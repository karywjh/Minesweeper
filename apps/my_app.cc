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
using cinder::Rectf;
using std::vector;

using board::Location;

MyApp::MyApp() : board_{board::Board()} {}

void MyApp::setup() {
  image1 = ci::gl::Texture::create(cinder::loadImage(cinder::app::loadAsset("Images/0.png")));
  image2 = ci::gl::Texture::create(cinder::loadImage(cinder::app::loadAsset("Images/1.png")));
}

void MyApp::update() {
}

void MyApp::draw() {
//   Set Background Color to Black
  cinder::gl::clear(Color(0, 0, 0));

  DrawStart();
  DrawGrid();
}

void MyApp::keyDown(KeyEvent event) {
}

void MyApp::mouseDown(MouseEvent event) {
  if (event.isLeftDown()) {
    int row = event.getY() / kCellSize_;
    int col = event.getX() / kCellSize_;
    std::cout << "Row: " << row << std::endl;
    std::cout << "Col: " << col << std::endl;

    this->board_.GenerateBoard(16, 16, 40, Location(row, col));

    if (this->board_.cells_[row][col].state_ != board::Cell::CellState::FLAGGED) {
      this->board_.cells_[row][col].ChangeState(board::Cell::CellState::OPENED);
    }
  }

  if (event.isRightDown()) {
    int row = event.getY() / kCellSize_;
    int col = event.getX() / kCellSize_;

    if (this->board_.cells_[row][col].state_ == board::Cell::CellState::FLAGGED) {
      this->board_.cells_[row][col].ChangeState(board::Cell::CellState::COVERED);
      this->board_.mine_count_++; // Total mine count increased by one
    } else if (this->board_.cells_[row][col].state_ == board::Cell::CellState::COVERED) {
      this->board_.cells_[row][col].ChangeState(board::Cell::CellState::FLAGGED);
      this->board_.mine_count_--; // Total mine count decreased by one
    }
  }
}


void MyApp::DrawStart(){
  // Letting User to Select Settings for Game
  // Initiate board_
  board_.InitProperties(16, 16, 40); // test code
}

void MyApp::DrawGrid() {
  // Change the window size depending on the board size.
  setWindowSize(board_.width_ * kCellSize_, board_.height_ * kCellSize_);

  this->board_.GenerateBoard(16, 16, 40, board::Location(0, 0));
  vector<vector<board::Cell>> board = this->board_.cells_;

  // Loop through every cell of board, draw every cell
  for (int row = 0; row < this->board_.height_; row++) {
    for (int col = 0; col < this->board_.width_; col++) {
      board::Cell curr_cell = this->board_.cells_[row][col];
      cinder::Rectf rect(col * kCellSize_, row * kCellSize_,
                         (col + 1) * kCellSize_, (row + 1) * kCellSize_);

      cinder::gl::draw(curr_cell.image_,rect);
    }
  }

//  cinder::gl::draw(image1, cinder::Rectf(0, 0, cell_size_, cell_size_));
//
//  cinder::Rectf rectf(cell_size_, 0, cell_size_ + 30,  cell_size_);
//  cinder::gl::draw(image2, rectf);
}

}  // namespace myapp
