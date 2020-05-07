// Copyright (c) 2020 [Kary Wang]. All rights reserved.

#ifndef FINALPROJECT_CELL_H
#define FINALPROJECT_CELL_H

#include <cinder/gl/Texture.h>
#include "location.h"

namespace board {

using cinder::gl::TextureRef;
using board::Location;

class Cell {
 public:

  enum CellState {
    COVERED,
    FLAGGED,
    OPENED,
  };

  int value_; // #0-8, or -1 as mine
  int real_value_; // decrease as mines around are opened
  std::string image_; // displayed in GUI corresponding to its state & value
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

  bool IsSafe();

  /**
   * Get the Image texture after cell state had been changed.
   * (player had clicked or flagged the cell)
   * @param new_state New state of the cell after player's move
   * @return image to be displayed after the change of state
   */
  void ChangeState(CellState new_state);
};
}  // namespace board

#endif  // FINALPROJECT_CELL_H
