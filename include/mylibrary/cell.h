// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef FINALPROJECT_CELL_H
#define FINALPROJECT_CELL_H

#include <cinder/gl/Texture.h>

namespace board {

using cinder::gl::TextureRef;

// Position of Cells start from {0, 0}
struct Position {
  int x;
  int y;

  bool operator<(const Position& position) const {
    return (x < position.x) ||
           (y < position.y);
  }
};

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
  Position position_;

  Cell();
  explicit Cell(int value, Position position);

  /**
   * Initiate the value and position of Cell.
   * @param value initial value
   * @param position position of Cell
   */
  void InitCell(int value, Position position);

  /**
   * Get the Image texture after cell state had been changed.
   * (player had clicked or flagged the cell)
   * @param new_state New state of the cell after player's move
   * @return image to be displayed after the change of state
   */
  TextureRef GetChangedImage(CellState new_state);

  /**
   * Compare two Cells. Used for inserting into a Set of Cells.
   */
  bool operator<(const Cell& cell) const;
};
}  // namespace board

#endif  // FINALPROJECT_CELL_H
