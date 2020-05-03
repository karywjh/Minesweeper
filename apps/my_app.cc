// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/Window.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/wrapper.h>
#include <cinder/gl/gl.h>

#include <vector>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::app::MouseEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;

using std::string;
using std::vector;

using board::Location;

const char kNormalFont[] = "Arial";

MyApp::MyApp()
    : engine_{}, state_{AppState::kSetting} {}

void MyApp::setup() {
}

void MyApp::update() {
}

void MyApp::draw() {
//   Set Background Color to Black
  cinder::gl::clear(Color(0, 0, 0));

  board::GameState game_state = this->engine_.GetState();

  switch (game_state) {
    case board::GameState::kNotStarted:
      DrawStart();
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
      DrawGrid();
      DrawWin();
      break;
    }
  }
}

void MyApp::keyDown(KeyEvent event) {
}

void MyApp::mouseDown(MouseEvent event) {
  int row = event.getY() / kCellSize_;
  int col = event.getX() / kCellSize_;
  board::GameState game_state = this->engine_.GetState();

  if (event.isLeftDown()) {
    if (game_state == board::GameState::kNotStarted && this->engine_.StartGame(row, col)) {
      this->engine_.OpenCell(row, col);
      // TODO: Start timer
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


void MyApp::DrawStart() {
  // Letting User to Select Settings for Game
  // Initiate board_
  engine_.Init(16, 16, 40); // TODO: Change numbers later

  // Change the window size depending on the board size.
  board::Board board = this->engine_.GetBoard();
  setWindowSize(board.width_ * kCellSize_, board.height_ * kCellSize_);
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
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};

  std::stringstream s;
  s << "You Lose!";
  PrintText(s.str(), Color::white(), size, center);
}

void MyApp::DrawWin() {
  // Draw scoreboard
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};

  std::stringstream s;
  s << "You Win!";
  PrintText(s.str(), Color::white(), size, center);
}


}  // namespace myapp
