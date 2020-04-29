// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef FINALPROJECT_CELL_H
#define FINALPROJECT_CELL_H

#include <cinder/gl/Texture.h>
#include "location.h"

namespace board {

using cinder::gl::TextureRef;
using board::Location;
// Position of Cells start from {0, 0}
//struct Position {
//  int row;
//  int col;
//
//  bool operator<(const Position& position) const {
//    return (row < position.row) ||
//           (col < position.col);
//  }
//};

class Cell {
 public:

  enum CellState {
    COVERED,
    FLAGGED,
    OPENED,
  };

  int value_; // #0-8, or -1 as mine
  TextureRef image_; // displayed in GUI corresponding to its state & value
  CellState state_;
  Location location_;

  Cell();
  explicit Cell(int value, Location location);

  /**
   * Initiate the value and location of Cell.
   * @param value initial value
   * @param location location of Cell
   */
  void InitCell(int value, Location location);

  /**
   * Get the Image texture after cell state had been changed.
   * (player had clicked or flagged the cell)
   * @param new_state New state of the cell after player's move
   * @return image to be displayed after the change of state
   */
  TextureRef GetChangedImage(CellState new_state);
};
}  // namespace board

#endif  // FINALPROJECT_CELL_H
