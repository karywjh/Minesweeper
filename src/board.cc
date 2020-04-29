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

//  this->start_loc_ = Location(0, 0);
}

// unused
//Board::Board(int width, int height, Location start) {
//  this->width_ = width;
//  this->height_ = height;
//  this->mine_count_ = width * height / 5;
//  this->start_loc_ = start;
//}
//
//// unused
//Board::Board(int width, int height, int mine_count, Location start) {
//  this->width_ = width;
//  this->height_ = height;
//  this->mine_count_ = mine_count;
//  this->start_loc_ = start;
//}

void Board::InitProperties(const int width, const int height,
                           const int mine_count) {
  this->width_ = width;
  this->height_ = height;
  this->mine_count_ = mine_count;

  // Set the size for 2D Cell vector
  this->cells_.resize(height);

  for (int i = 0; i < height; i++) {
    cells_.at(i).resize(width);
  }
}

int Board::CountSurroundingMines(const int row, const int col) {

}


void Board::GenerateMines() {
  srand(this->id_);

  // Generate Random Location to place mines.
  // Insert the Locations into the set.
  while (this->mine_pos_.size() < this->mine_count_) {
    this->mine_pos_.insert(Location(rand() % this->height_, rand() % this->width_));
  }

  for (Location loc: this->mine_pos_) {
    this->cells_[loc.Row()][loc.Col()].InitCell(-1, loc);
  }
}

void Board::FillInValues() {
  for (int row = 0; row < this->height_; row++) {
    for (int col = 0; col < this->width_; col++) {
      board::Cell curr_cell = this->cells_[row][col];
      curr_cell.InitCell(CountSurroundingMines(row, col), Location(row, col));
    }
  }
}

void Board::GenerateBoard(const int width, const int height, const int mines, Location start) {
  // Set start location to have value 0
//  this->start_loc_ = start;
  this->cells_[start.Row()][start.Col()].InitCell(0, start);

  // Randomly Place Mines and fill in rest of the board
  GenerateMines();
//  FillInValues();

//  std::set<Location> loc;
//  loc.insert(Location(2, 2));
//  loc.insert(Location(4, 5));
//  loc.insert(Location(2, 2));
//  loc.insert(Location(1, 3));
//
//  std::cout << loc.size() << std::endl;
}

}  // namespace board