// Copyright (c) 2020 [Kary Wang]. All rights reserved.

#include "my_app.h"

#include <CinderImGui.h>
#include <cinder/app/Window.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/wrapper.h>
#include <cinder/app/App.h>

#include <chrono>
#include <string>
#include <cstring>
#include <sstream>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::app::MouseEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::gl::TextureRef;
using cinder::gl::Texture;

using std::string;
using std::vector;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using board::Location;

const char kDbPath[] = "minesweeper.db";
const size_t kLimit = 3;
const size_t kWidthMin = 9;
const size_t kWidthMax = 60;
const size_t kHeightMin = 9;
const size_t kHeightMax = 25;
const size_t kMinesMin = 10;


MyApp::MyApp()
    : engine_{},
      leaderboard_{cinder::app::getAssetPath(kDbPath).string()},
      start_time_{system_clock::now()},
      game_time_{0},
      update_scores_{false},
      name_{"N/A"},
      player_{},
      sound_{true} {}

void MyApp::setup() {
  ui::initialize();

  cinder::audio::SourceFileRef clickSound =
      cinder::audio::load(cinder::app::loadAsset("click.wav"));
  this->click_sound_ = cinder::audio::Voice::create(clickSound);

  cinder::audio::SourceFileRef flagSound =
      cinder::audio::load(cinder::app::loadAsset("flag.wav"));
  this->flag_sound_ = cinder::audio::Voice::create(flagSound);

  cinder::audio::SourceFileRef bombSound =
      cinder::audio::load(cinder::app::loadAsset("bomb.wav"));
  this->bomb_sound_ = cinder::audio::Voice::create(bombSound);
  this->bomb_sound_->setVolume(0.2);

  // Create and load all images of cells
  for (int i = 0; i <= 8; i++) {
    this->images_.push_back(Texture::create(cinder::loadImage(
        cinder::app::loadAsset("Images/" + std::to_string(i) + ".png"))));
  }

  this->images_.push_back(Texture::create(
      cinder::loadImage(cinder::app::loadAsset("Images/facingDown.png"))));
  this->images_.push_back(Texture::create(
      cinder::loadImage(cinder::app::loadAsset("Images/flagged.png"))));
  this->images_.push_back(Texture::create(
      cinder::loadImage(cinder::app::loadAsset("Images/bomb.png"))));
}

void MyApp::update() {
  if (this->update_scores_) {
    if (this->top_overall_players_.empty()) {
      leaderboard_.AddScoreToLeaderBoard(
          {this->name_, this->game_time_, this->engine_.GetBoard().id_,
           this->engine_.GetBoard().width_, this->engine_.GetBoard().height_,
           this->engine_.GetBoard().initial_mine_count_});

      this->player_ = board::Player(
          this->name_, this->game_time_, this->engine_.board_.id_,
          this->engine_.board_.width_, this->engine_.board_.height_,
          this->engine_.board_.initial_mine_count_);

      this->top_overall_players_ = this->leaderboard_.RetrieveLeastTimes(
          this->player_.width, this->player_.height, this->player_.mines,
          kLimit);

      this->top_id_players_ = this->leaderboard_.RetrieveLeastTimes(
          this->player_.id, this->player_.width, this->player_.height,
          this->player_.mines, kLimit);

      this->personal_tops_ =
          this->leaderboard_.RetrieveLeastTimes(this->player_, kLimit);

      // It is crucial the this vector be populated, given that `kLimit` > 0.
      assert(!this->top_overall_players_.empty());
      assert(!this->top_id_players_.empty());
      assert(!this->personal_tops_.empty());
    }
    return;
  }
}

void MyApp::draw() {
//   Set Background Color to Black
  cinder::gl::clear(Color(0, 0, 0));

  board::GameState game_state = this->engine_.GetState();

  switch (game_state) {
    case board::GameState::kSetting:
      DrawStart();
      break;
    case board::GameState::kNotStarted: {
      // Change the window size depending on the board size.
      setWindowSize(this->engine_.GetBoard().width_ * kCellSize_,
                    this->engine_.GetBoard().height_ * kCellSize_);
      DrawGrid();
      break;
    }
    case board::GameState::kPlaying: {
      DrawGrid();
      break;
    }
    case board::GameState::kLose: {
      this->engine_.OpenAllMines();
      if (this->sound_) {
        this->bomb_sound_->start();
        this->sound_ = false;
      }

      DrawGrid();
      DrawLose();
      break;
    }
    case board::GameState::kWin: {
      if (!this->update_scores_) {
        this->game_time_ =
            (duration_cast<seconds>(system_clock::now() - this->start_time_))
                .count();
        this->update_scores_ = true;
        DrawGrid();
      } else {
        DrawGrid();
        DrawWin();
        break;
      }
    }
  }
}

void MyApp::keyDown(KeyEvent event) {
  if (this->engine_.state_ == board::GameState::kSetting) {
    if (event.getCode() == KeyEvent::KEY_RETURN ||
        event.getCode() == KeyEvent::KEY_KP_ENTER) {
      this->engine_.state_ = board::GameState::kNotStarted;
    }
  }

}

void MyApp::mouseDown(MouseEvent event) {
  int row = event.getY() / kCellSize_;
  int col = event.getX() / kCellSize_;
  board::GameState game_state = this->engine_.GetState();

  if (event.isLeftDown()) {
    if (this->engine_.board_.cells_[row][col].state_ ==
        board::Cell::CellState::COVERED) {
      this->click_sound_->start();
    }

    if (game_state == board::GameState::kNotStarted &&
        this->engine_.StartGame(row, col)) {
      this->engine_.OpenCell(row, col);
      this->start_time_ = system_clock::now();
    }

    if (game_state == board::GameState::kPlaying) {
      this->engine_.OpenCell(row, col);
    }
  }

  if (event.isRightDown()) {
    if (game_state == board::GameState::kPlaying) {
      this->engine_.FlagCell(row, col);
      this->flag_sound_->start();
    }
  }
}

// Letting User to Select Settings for Game
// Initiate board_
void MyApp::DrawStart() {
  // Initiate setting window
  ui::ScopedWindow window("Settings");
  ui::SetWindowPos(ImVec2(0, 0));
  ui::SetWindowSize(cinder::app::getWindowSize());

  std::string default_n = this->name_;
  if (ui::InputText("Name", &default_n, 24)) {
    this->name_ = default_n;
  }

  // Set id
  int id = this->engine_.board_.id_;
  if (ui::InputInt("Board ID", &id)) {
    this->engine_.board_.id_ = id;
  }

  // Set three level buttons
  if (ui::Button("Beginner (9x9, 10 mines)", ImVec2(ui::GetWindowWidth(), 0))) {
    this->engine_.Init(9, 9, 10);
    this->engine_.state_ = board::GameState::kNotStarted;
    return;
  }

  if (ui::Button("Intermediate (16x16, 40 mines)",
                 ImVec2(ui::GetWindowWidth(), 0))) {
    this->engine_.Init(16, 16, 40);
    this->engine_.state_ = board::GameState::kNotStarted;
    return;
  }

  if (ui::Button("Advanced (16x30, 99 mines)",
                 ImVec2(ui::GetWindowWidth(), 0))) {
    this->engine_.Init(30, 16, 99);
    this->engine_.state_ = board::GameState::kNotStarted;
    return;
  }

  if (ui::TreeNode("Custom")) {
    ui::Unindent();

    // Sliders for width, height, mines.
    int width = this->engine_.GetBoard().width_;
    ui::SliderInt("width", &width, kWidthMin, kWidthMax);

    int height = this->engine_.GetBoard().height_;
    ui::SliderInt("height", &height, kHeightMin, kHeightMax);

    int mines = this->engine_.GetBoard().initial_mine_count_;
    int max = int (width * height * 0.8);
    ui::SliderInt("mine count", &mines, kMinesMin, max);

    if (ui::Button("Start")) {
      this->engine_.state_ = board::GameState::kNotStarted;
    }

    this->engine_.Init(width, height, mines);
    ui::TreePop();
  }
}

void MyApp::DrawGrid() {
  board::Board board = this->engine_.GetBoard();

  // Loop through every cell of board, draw every cell
  for (int row = 0; row < board.height_; row++) {
    for (int col = 0; col < board.width_; col++) {
      board::Cell curr_cell = board.cells_[row][col];
      cinder::Rectf rect(col * kCellSize_, row * kCellSize_,
                         (col + 1) * kCellSize_, (row + 1) * kCellSize_);

      cinder::gl::draw(this->images_[curr_cell.image_index_], rect);
    }
  }
}

void MyApp::DrawLose() {
  ui::ScopedWindow window("Game Ends");
  ui::SetWindowPos(ImVec2(0, 0));
  ui::SetWindowSize(cinder::app::getWindowSize());

  ui::SetCursorPosX(cinder::app::getWindowWidth() / 2 - 35);
  ui::SetWindowFontScale(1.5);
  ui::Text("You lose!");

  if (ui::Button("New Game", ImVec2(ui::GetWindowWidth(), 0))) {
    ResetGame();
  }
}

void MyApp::DrawLeaderBoard(const char* title,
                            const std::vector<board::Player>& players) {
  if (ui::TreeNode(title)) {
    ui::Text("Name:");
    ui::SameLine(cinder::app::getWindowWidth() - 60);
    ui::Text("Time (s)");

    for (const board::Player& player : players) {
      std::string name = player.name;
      char cstr[name.size() + 1];
      strcpy(cstr, name.c_str());
      ui::Text("%s", cstr);

      ui::SameLine(cinder::app::getWindowWidth() - 45);

      std::stringstream ss;
      ss << player.time;
      ui::Text("%s", (char*)ss.str().c_str());
    }
    ui::TreePop();
  }
}

void MyApp::DrawWin() {
  // Draw scoreboard
  ui::ScopedWindow window("Game Ends");
  ui::SetWindowPos(ImVec2(0, 0));
  ui::SetWindowSize(cinder::app::getWindowSize());

  ui::SetCursorPosX(cinder::app::getWindowWidth() / 2 - 35);
  ui::AlignTextToFramePadding();
  ui::SetWindowFontScale(1.5);
  ui::Text("You Win!");

  std::stringstream ss;
  ss << "Your time: " << this->game_time_ << "s";
  ui::Text("%s", ss.str().c_str());

  ss.str("");
  ss << "Your best time: " << this->personal_tops_[0].time << "s";
  ui::Text("%s", ss.str().c_str());

  ss.str("");
  ss << "Your average time: "
     << this->leaderboard_.GetAverageTime(this->player_) << "s";
  ui::Text("%s", ss.str().c_str());

  ss.str("");
  ss << "Total Wins: "
     << this->leaderboard_.GetTotalWins(this->player_);
  ui::Text("%s", ss.str().c_str());

  // Draw leader board for top overall players
  ss.str("");
  ss << "Overall Top (" << this->engine_.board_.height_ << "x"
     << this->engine_.board_.width_ << ", "
     << this->engine_.board_.initial_mine_count_ << ")";
  DrawLeaderBoard((char*) ss.str().c_str(), this->top_overall_players_);

  // Draw leader board for top overall players
  ss.str("");
  ss << "Top for ID " << this->engine_.board_.id_;
  DrawLeaderBoard((char*) ss.str().c_str(), this->top_id_players_);

  ss.str("");
  ss << this->name_ << "'s Personal Top";
  DrawLeaderBoard((char*) ss.str().c_str(), this->personal_tops_);

  if (ui::Button("New Game", ImVec2(ui::GetWindowWidth(), 0))) {
    ResetGame();
  }
}

void MyApp::ResetGame() {
  this->engine_.Reset();
  this->top_overall_players_.clear();
  this->top_id_players_.clear();
  this->update_scores_ = false;
  this->sound_ = true;
}


}  // namespace myapp
