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

bool Board::IsMine(const Location& loc) {
  return this->cells_[loc.Row()][loc.Col()].value_ < 0;
}

set<Location> Board::GetNeighbors(const Location& loc) {
  Location up = loc + Location(-1, 0);
  Location down = loc + Location(1, 0);
  Location right = loc + Location(0, 1);
  Location left = loc + Location(0, -1);
  Location up_right = loc + Location(-1, 1);
  Location up_left = loc + Location(-1, -1);
  Location down_right = loc + Location(1, 1);
  Location down_left = loc + Location(1, -1);

  set<Location> neighbors;

  if (up.IsValidLoc(this->height_, this->width_)) {
    neighbors.insert(up);
  }
  if (down.IsValidLoc(this->height_, this->width_)) {
    neighbors.insert(down);
  }
  if (right.IsValidLoc(this->height_, this->width_)) {
    neighbors.insert(right);
  }
  if (left.IsValidLoc(this->height_, this->width_)) {
    neighbors.insert(left);
  }
  if (up_right.IsValidLoc(this->height_, this->width_)) {
    neighbors.insert(up_right);
  }
  if (up_left.IsValidLoc(this->height_, this->width_)) {
    neighbors.insert(up_left);
  }
  if (down_right.IsValidLoc(this->height_, this->width_)) {
    neighbors.insert(down_right);
  }
  if (down_left.IsValidLoc(this->height_, this->width_)) {
    neighbors.insert(down_left);
  }

  return neighbors;
}


int Board::CountSurroundingMines(const Location& loc) {
  int mines = 0;
  set<Location> neighbors = GetNeighbors(loc);

  for (Location loc: neighbors) {
    if (IsMine(loc)) {
      mines++;
    }
  }

  return mines;
}

void Board::GenerateMines(const Location& start) {
  srand(this->id_);

  // All cells that are neighbor to starting location can't be mines
  set<Location> non_mine_loc = GetNeighbors(start);
  non_mine_loc.insert(start);

  // Generate Random Location to place mines.
  // Insert the Locations into the set.
  while (this->mine_pos_.size() <= this->mine_count_) {
    Location new_loc = Location(rand() % this->height_, rand() % this->width_);
    if (non_mine_loc.find(new_loc) == non_mine_loc.end()) {
      this->mine_pos_.insert(new_loc);
    }
  }

  for (Location loc: this->mine_pos_) {
    this->cells_[loc.Row()][loc.Col()].InitCell(-1, loc);
  }
}

void Board::FillInValues() {
  for (int row = 0; row < this->height_; row++) {
    for (int col = 0; col < this->width_; col++) {
      if (this->cells_[row][col].value_ >= 0) {
        Location loc = Location(row, col);
        this->cells_[row][col].InitCell(CountSurroundingMines(loc), loc);
      }
    }
  }
}

void Board::GenerateBoard(const int width, const int height, const int mines, const Location& start) {
  // Set start location to have value 0
//  this->start_loc_ = start;
  this->cells_[start.Row()][start.Col()].InitCell(0, start);

  // Randomly Place Mines and fill in rest of the board
  GenerateMines(start);
  FillInValues();

//  std::set<Location> loc;
//  loc.insert(Location(2, 2));
//  loc.insert(Location(4, 5));
//  loc.insert(Location(2, 2));
//  loc.insert(Location(1, 3));
//
//  std::cout << loc.size() << std::endl;
}

}  // namespace board