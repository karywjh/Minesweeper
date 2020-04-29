// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/board.h>
#include <set>

#include <iostream>

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

  // Set the size for Cell** board_
  this->board_.resize(height);

  for (int i = 0; i < height; i++) {
    board_.at(i).resize(width);
  }
}


Cell** Board::GenerateBoard(const int width, const int height, const int mines, Position start) {
  // Set start position to have value 0
  this->board_[start.y][start.x].InitCell(0, start);

  // Randomly Place Mines and fill in rest of the board
  GenerateMines();
  FillInValues();

  std::set<Cell> cells;
  cells.insert(Cell(1, Position{2,2}));
  cells.insert(Cell(2, Position{4,5}));
  cells.insert(Cell(3, Position{2, 2}));
  cells.insert(Cell(3, Position{1, 3}));

}

}  // namespace board