// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef FINALPROJECT_BOARD_H
#define FINALPROJECT_BOARD_H

#include <mylibrary/cell.h>
namespace board {

const int kDefaultWidth = 9;
const int kDefaultLength = 9;
const int kDefaultMines = 10;

struct Position {
  int x;
  int y;

//  bool operator <(const Position& left, const Position& right);
};

class Board {
 public:
  int width_;
  int length_;
  int mine_count_;
  Position start_pos_;
  Cell** board_;

  Board(Position start);
  Board(int width, int length, Position start);
  Board(int width, int length, int mine_count, Position start);
  // TBA: 3D Board

  // Total number of cells in the board.
  int GetTotalCells();

  // Count total number of non-flagged mines left.
  int GetMinesLeft();

  // Count how many mines is next to the cell.
  int CountSurroundingMines(const int x, const int y);

  // Randomly assign mines to cells.
  void GenerateMines();

  // Based on how many mines are around the cell,
  // fill in the blank cells that are not mines.
  void FillInValues();

  Cell** GenerateBoard(const int width, const int length, const int mines, Position start_pos);
};


}  // namespace board

#endif  // FINALPROJECT_BOARD_H
