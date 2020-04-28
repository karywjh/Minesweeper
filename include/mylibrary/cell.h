// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef FINALPROJECT_CELL_H
#define FINALPROJECT_CELL_H

#include <cinder/gl/Texture.h>

namespace board {

using cinder::gl::TextureRef;

class Cell {
 public:

  enum CellState {
    COVERED,
    FLAGGED,
    OPENED,
  };

  int value_; // #0-8, or -1 as mine
  TextureRef image_; // image displayed in GUI corresponding to cell state
  CellState state_;

  explicit Cell(int value);

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
