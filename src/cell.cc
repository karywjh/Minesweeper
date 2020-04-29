// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/cell.h>
#include <cinder/app/App.h>

namespace board {

using cinder::gl::Texture;

Cell::Cell() {
  this->value_ = 0;
  this->state_ = CellState::COVERED;
  this->image_ = Texture::create(cinder::loadImage(
      cinder::app::loadAsset("Images/facingDown.png")));
  this->position_ = Position{0, 0};
}

Cell::Cell(int value, Position position) {
    this->value_ = value;
    this->state_ = CellState::COVERED;
    this->image_ = Texture::create(cinder::loadImage(
        cinder::app::loadAsset("Images/facingDown.png")));
    this->position_ = position;
}

void Cell::InitCell(int value, Position position) {
  this->value_ = value;
  this->position_ = position;
}

TextureRef Cell::GetChangedImage(CellState new_state) {
  this->state_ = new_state;

  // change image corresponding to new state
  switch (new_state) {
    case CellState::COVERED: {
      this->image_ = Texture::create(cinder::loadImage(
          cinder::app::loadAsset("Images/facingDown.png")));
      break;
    }

    case CellState::FLAGGED: {
      this->image_ = Texture::create(cinder::loadImage(
          cinder::app::loadAsset("Images/flagged.png")));
      break;
    }

    case CellState::OPENED: {
      // Display bomb image if value is -1 (cell is bomb)
      if (this->value_ < -1) {
        this->image_ = Texture::create(
            cinder::loadImage(cinder::app::loadAsset("Images/bomb.png")));
      } else {
        this->image_ = Texture::create(cinder::loadImage(cinder::app::loadAsset(
            "Images/" + std::to_string(this->value_) + ".png")));
      }
      break;
    }
  }
}

bool Cell::operator<(const Cell& cell) const {
  return (this->position_.x < cell.position_.x) ||
         (this->position_.y < cell.position_.y);
}

}  // namespace board