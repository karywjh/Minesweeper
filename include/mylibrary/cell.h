// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef FINALPROJECT_CELL_H
#define FINALPROJECT_CELL_H

#include <cinder/gl/Texture.h>

namespace board {

class Cell {
 public:

  enum CellState {
    COVERED,
    FLAGGED,
    OPENED,
  };

  int value_; // #0-8, or -1 as mine
  ci::gl::TextureRef image_;
  CellState state_;

  explicit Cell(int value);

};
}  // namespace board

#endif  // FINALPROJECT_CELL_H
