// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef FINALPROJECT_BOARD_H
#define FINALPROJECT_BOARD_H

#include <set>
#include <mylibrary/cell.h>

namespace board {

using std::vector;

const int kDefaultWidth = 9;
const int kDefaultLength = 9;
const int kDefaultMines = 10;

class Board {
 public:
  int width_;
  int height_;
  int mine_count_;
  Position start_pos_;
  vector<vector<Cell>> board_;
  int id_; // id representing a board

  Board();
  Board(int width, int height, Position start);
  Board(int width, int height, int mine_count, Position start);
  // TBA: 3D Board
  // TBA: Board with ID

  void InitProperties(const int width, const int height, const int mine_count);

  // Count total number of non-flagged mines left.
  int GetMinesLeft();

  // Count how many mines is next to the cell.
  int CountSurroundingMines(const int x, const int y);

  // Randomly assign mines to cells.
  std::set<Position> GenerateMines();

  // Based on how many mines are around the cell,
  // fill in the blank cells that are not mines.
  void FillInValues();

  Cell** GenerateBoard(const int width, const int height, const int mines, Position start);
};


}  // namespace board

#endif  // FINALPROJECT_BOARD_H
