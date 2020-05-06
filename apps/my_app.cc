// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <CinderImGui.h>
#include <cinder/app/Window.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/wrapper.h>

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

using std::string;
using std::vector;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;


using board::Location;

const char kNormalFont[] = "Arial";
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
      name_{"N/A"} {}

void MyApp::setup() {
    ui::initialize();
}

void MyApp::update() {
  if (this->update_scores_) {
    if (this->top_overall_players_.empty()) {
      leaderboard_.AddScoreToLeaderBoard(
          {this->name_, this->game_time_, this->engine_.GetBoard().id_,
           this->engine_.GetBoard().width_, this->engine_.GetBoard().height_,
           this->engine_.GetBoard().initial_mine_count_});

      this->top_overall_players_ = leaderboard_.RetrieveLeastTimes(
          this->engine_.board_.width_, this->engine_.board_.height_,
          this->engine_.board_.initial_mine_count_, kLimit);

      this->top_id_players_ = leaderboard_.RetrieveLeastTimes(
          this->engine_.board_.id_, this->engine_.board_.width_,
          this->engine_.board_.height_, this->engine_.board_.initial_mine_count_,
          kLimit);

      // It is crucial the this vector be populated, given that `kLimit` > 0.
      assert(!this->top_overall_players_.empty());
      assert(!this->top_id_players_.empty());
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
      setWindowSize(this->engine_.GetBoard().width_ * kCellSize_, this->engine_.GetBoard().height_ * kCellSize_);
      DrawGrid();
      break;
    }
    case board::GameState::kPlaying: {
      DrawGrid();
      break;
    }
    case board::GameState::kLose: {
      this->engine_.OpenAllMines();
      DrawGrid();
      DrawLose();
      break;
    }
    case board::GameState::kWin: {
      this->game_time_ = (duration_cast<seconds>(system_clock::now() - this->start_time_)).count();
      this->update_scores_ = true;
      DrawGrid();
      DrawWin();
      break;
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
    if (game_state == board::GameState::kNotStarted && this->engine_.StartGame(row, col)) {
      this->engine_.OpenCell(row, col);
      // TODO: Start timer
      this->start_time_ = system_clock::now();
    }

    if (game_state == board::GameState::kPlaying) {
      this->engine_.OpenCell(row, col);
    }
  }

  if (event.isRightDown()) {
    if (game_state == board::GameState::kPlaying) {
      this->engine_.FlagCell(row, col);
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

  if (ui::InputText("Name", &this->name_, 24)) {
    std::cout << this->name_ << std::endl;
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

    int mines = this->engine_.GetBoard().mine_count_;
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

      cinder::gl::draw(curr_cell.image_,rect);
    }
  }
}

// Got From Snake Game
template <typename C>
void PrintText(const string& text, const C& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 30))
      .size(size)
      .color(color)
      .backgroundColor(ColorA(0, 0, 0, 0))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
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
  ss << "Overall Top (" << this->engine_.board_.height_ << "x" << this->engine_.board_.width_ << ", " << this->engine_.board_.mine_count_ << ")";

  if (ui::TreeNode((char*) ss.str().c_str())) {
    ui::Text("Name:");
    ui::SameLine(cinder::app::getWindowWidth() - 60);
    ui::Text("Time (s)");

    for (const board::Player& player: this->top_overall_players_) {
      ui::AlignTextToFramePadding();

      std::string name = player.name;
      char cstr[name.size() + 1];
      strcpy(cstr, name.c_str());
      ui::Text("%s", cstr);

      ui::SameLine(cinder::app::getWindowWidth() - 45);

      std::stringstream ss;
      ss << player.time;
      ui::Text("%s", (char*) ss.str().c_str());
    }
    ui::TreePop();
  }

  ss.str("");
  ss << "Top for ID " << this->engine_.board_.id_;
  if (ui::TreeNode((char*) ss.str().c_str())) {
    ui::Text("Name:");
    ui::SameLine(cinder::app::getWindowWidth() - 60);
    ui::Text("Time (s)");

    for (const board::Player& player: this->top_id_players_) {
      ui::AlignTextToFramePadding();

      std::string name = player.name;
      char cstr[name.size() + 1];
      strcpy(cstr, name.c_str());
      ui::Text("%s", cstr);

      ui::SameLine(cinder::app::getWindowWidth() - 45);

      std::stringstream ss;
      ss << player.time;
      char const *pchar = (char*) ss.str().c_str();
      ui::Text("%s", pchar);
    }
    ui::TreePop();
  }


  if (ui::Button("New Game", ImVec2(ui::GetWindowWidth(), 0))) {
    ResetGame();
  }
}

void MyApp::ResetGame() {
  this->engine_.Reset();
  this->top_overall_players_.clear();
  this->top_id_players_.clear();
  this->update_scores_ = false;
  this->name_ = "N/A";
}


}  // namespace myapp
