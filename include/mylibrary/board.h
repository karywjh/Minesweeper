// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef FINALPROJECT_BOARD_H
#define FINALPROJECT_BOARD_H

#include <set>
#include "cell.h"

namespace board {

using std::vector;
using std::set;

const int kDefaultWidth = 9;
const int kDefaultLength = 9;
const int kDefaultMines = 10;

class Board {
 public:
  int width_;
  int height_;
  int mine_count_;
//  Location start_loc_;
  vector<vector<Cell>> cells_;
  int id_; // id representing a board

  set<Location> non_mine_;
  set<Location> mine_loc_;
  set<Location> zero_cells_;

  Board();
//  Board(int width, int height, Location start);
//  Board(int width, int height, int mine_count, Location start);
  // TBA: 3D Board
  // TBA: Board with ID

  // Initiate board with player selected width, height and mine_count
  void InitProperties(const int width, const int height, const int mine_count);

  // True if the selected location is mine
  bool IsMine(const Location& loc);

  // Get a set of all locations that are neighbors of a given location
  set<Location> GetNeighbors(const Location& loc);

  // Count total number of non-flagged mines left.
  int GetMinesLeft();

  // Count how many mines is next to the cell.
  int CountSurroundingMines(const Location& loc);

  // Randomly assign mines to cells.
  void GenerateMines(const Location& start);

  // Based on how many mines are around the cell,
  // fill in the blank cells that are not mines.
  void FillInValues();

  void GenerateBoard(const Location& start);

  void OpenNeighbors(const Location& location);

  void OpenAllZeroNeighbors();

  void AutoOpen(const Location& location, bool open_more);
};


}  // namespace board

#endif  // FINALPROJECT_BOARD_H
