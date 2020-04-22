// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef FINALPROJECT_CELL_H
#define FINALPROJECT_CELL_H

namespace board {

enum CellState {
  COVERED,
  FLAGGED,
  OPENED,
};

struct Cell {
  int value; // #0-8, or -1 as mine
  CellState state;
};

}  // namespace board

#endif  // FINALPROJECT_CELL_H
