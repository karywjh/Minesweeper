// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef FINALPROJECT_BOARD_H
#define FINALPROJECT_BOARD_H

namespace board {

class Board {
 public:
  int width_;
  int length_;
  int mine_count_;
  Cell** board[width_][length_];

  Board();
  Board(int width, int length);
  Board(int width, int length, int mine_count);
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
};


}  // namespace board

#endif  // FINALPROJECT_BOARD_H
