// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/board.h>

namespace board {

//bool Position& operator <(const Position& left) {
//  return (left.x < right.x) || (left.y < right.y);
//}

Board::Board(Position start) {
  this->width_ = kDefaultWidth;
  this->length_ = kDefaultLength;
  this->mine_count_ = kDefaultMines;
  this->start_pos_ = start;
}

Board::Board(int width, int length, Position start) {
  this->width_ = width;
  this->length_ = length;
  this->mine_count_ = width * length / 5;
  this->start_pos_ = start;
}

Board::Board(int width, int length, int mine_count, Position start) {
  this->width_ = width;
  this->length_ = length;
  this->mine_count_ = mine_count;
  this->start_pos_ = start;
}

int Board::GetTotalCells() {
  return width_ * length_;
}

}  // namespace board