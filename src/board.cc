// Copyright (c) 2020 [Kary Wang]. All rights reserved.

#include <mylibrary/board.h>
#include <time.h>
#include <stdlib.h>

#include <iostream>

namespace board {

Board::Board() {
  this->width_ = kDefaultWidth;
  this->height_ = kDefaultLength;
  this->initial_mine_count_ = kDefaultMines;
  this->mine_count_ = kDefaultMines;
  this->id_ = time(NULL);

//  this->start_loc_ = Location(0, 0);
}

void Board::InitProperties(const int width, const int height,
                           const int mine_count) {
  this->width_ = width;
  this->height_ = height;
  this->initial_mine_count_ = mine_count;
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
  set<Location> neighbors;
  set<Location> valid_neighbors;

  neighbors.insert(loc + Location(-1, 0));
  neighbors.insert(loc + Location(1, 0));
  neighbors.insert(loc + Location(0, 1));
  neighbors.insert(loc + Location(0, -1));
  neighbors.insert(loc + Location(-1, 1));
  neighbors.insert(loc + Location(-1, -1));
  neighbors.insert(loc + Location(1, 1));
  neighbors.insert(loc + Location(1, -1));

  // Get only valid neighbor locations
  for (Location location: neighbors) {
    if (location.IsValidLoc(this->height_, this->width_)) {
      valid_neighbors.insert(location);
    }
  }

  return valid_neighbors;
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

  while (this->mine_loc_.size() < this->initial_mine_count_) {
    // Generate Random Location to place mines.
    // Insert the Locations into the set.
    Location new_loc = Location(rand() % this->height_, rand() % this->width_);
    if (this->non_mine_.find(new_loc) == this->non_mine_.end()) {
      this->mine_loc_.insert(new_loc);
    }
  }

  // Init value of cells
  for (Location loc: this->mine_loc_) {
    this->cells_[loc.Row()][loc.Col()].InitCell(-1, loc);
  }
}

void Board::FillInValues() {
  for (int row = 0; row < this->height_; row++) {
    for (int col = 0; col < this->width_; col++) {
      if (this->cells_[row][col].value_ >= 0) {
        // this cell is non_mine cell
        Location loc = Location(row, col);
        this->non_mine_.insert(loc);

        // Initiate value of cell
        int value = CountSurroundingMines(loc);
        this->cells_[row][col].InitCell(value, loc);

        if (value == 0) {
          this->zero_cells_.insert(loc);
        }
      }
    }
  }
}

void Board::GenerateBoard(const Location& start) {
  // Set start location to have value 0
  this->cells_[start.Row()][start.Col()].InitCell(0, start);

  // All cells that are neighbor to starting location can't be mines
  this->non_mine_ = GetNeighbors(start);
  this->non_mine_.insert(start);

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

void Board::OpenZeroNeighbors(const Location& location) {
  if (this->cells_[location.Row()][location.Col()].value_ == 0) {
    for (Location loc: GetNeighbors(location)) {

      if (this->cells_[loc.Row()][loc.Col()].state_ !=
          board::Cell::CellState::OPENED) {
        this->cells_[loc.Row()][loc.Col()].ChangeState(
            board::Cell::CellState::OPENED);
        this->non_mine_.erase(loc);

        // Recursion to open neighbors of 0 cells if they are being opened
        OpenZeroNeighbors(loc);
      }
    }
  }
}

void Board::OpenNeighbors(const Location& location) {
  if (this->cells_[location.Row()][location.Col()].real_value_ == 0) {
    for (Location loc : GetNeighbors(location)) {

      if (!IsMine(loc)) {
        this->cells_[loc.Row()][loc.Col()].ChangeState(
            board::Cell::CellState::OPENED);
        this->non_mine_.erase(loc);

        // Recursion to open neighbors of 0 cells if they are being opened
        OpenZeroNeighbors(loc);
      }
    }
  }
}

void Board::UpdateNeighbor(const Location& location, const bool to_flag) {
  int row = location.Row();
  int col = location.Col();

  if (IsMine(location)) {
    // Flagged/Unflagged mine cell
    if (to_flag) {
      ChangeNeighborVals(location, -1);
    } else {
      ChangeNeighborVals(location, 1);
    }
  } else {
    // Flagged/Unflagged non-mine cell
    if (to_flag) {
      ChangeNeighborVals(location, -10);
    } else {
      ChangeNeighborVals(location, 10);
    }
  }
}

void Board::ChangeNeighborVals(const Location& location, const int val) {
  for (Location loc: GetNeighbors(location)) {
    if (!IsMine(loc)) {
      this->cells_[loc.Row()][loc.Col()].real_value_ += val;
    }
  }
}

}  // namespace board