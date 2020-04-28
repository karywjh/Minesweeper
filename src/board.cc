// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/board.h>

namespace board {

//bool Position& operator <(const Position& left) {
//  return (left.x < right.x) || (left.y < right.y);
//}

Board::Board() {
  this->width_ = kDefaultWidth;
  this->height_ = kDefaultLength;
  this->mine_count_ = kDefaultMines;
}

// unused
Board::Board(int width, int height, Position start) {
  this->width_ = width;
  this->height_ = height;
  this->mine_count_ = width * height / 5;
  this->start_pos_ = start;
}

// unused
Board::Board(int width, int height, int mine_count, Position start) {
  this->width_ = width;
  this->height_ = height;
  this->mine_count_ = mine_count;
  this->start_pos_ = start;
}

void Board::InitProperties(const int width, const int height,
                           const int mine_count) {
  this->width_ = width;
  this->height_ = height;
  this->mine_count_ = mine_count;
}

}  // namespace board