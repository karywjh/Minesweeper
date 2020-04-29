// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/board.h>
#include <time.h>
#include <stdlib.h>

#include <iostream>

namespace board {

Board::Board() {
  this->width_ = kDefaultWidth;
  this->height_ = kDefaultLength;
  this->mine_count_ = kDefaultMines;
  this->id_ = time(NULL);
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

std::set<Position> Board::GenerateMines() {
  std::set<Position> mines;
  srand(this->id_);

  // Generate Random Position to place mines.
  // Insert the positions into the set.
  while (mines.size() < this->mine_count_) {
    mines.insert(Position{rand() % this->width_, rand() % this->height_});
  }

  for (Position pos: mines) {
    this->board_[pos.y][pos.x].InitCell(-1, pos);
  }
  return mines;
}

Cell** Board::GenerateBoard(const int width, const int height, const int mines, Position start) {
  // Set start position to have value 0
  this->board_[start.y][start.x].InitCell(0, start);

  // Randomly Place Mines and fill in rest of the board
  GenerateMines();
//  FillInValues();

  std::set<Cell> cells;
  cells.insert(Cell(1, Position{2,2}));
  cells.insert(Cell(2, Position{4,5}));
  cells.insert(Cell(3, Position{2, 2}));
  cells.insert(Cell(3, Position{1, 3}));

}

}  // namespace board