// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/cell.h>
#include <cinder/app/App.h>
#include "cinder/app/RendererGl.h"

namespace board {

using cinder::gl::Texture;

Cell::Cell() {
  this->value_ = 0;
  this->real_value_ = 0;
  this->state_ = CellState::COVERED;
  this->image_ = Texture::create(cinder::loadImage(
      cinder::app::loadAsset("Images/facingDown.png")));
  this->location_ = Location(0, 0);
}

Cell::Cell(int value, Location location) {
  this->value_ = value;
  this->real_value_ = value;
  this->state_ = CellState::COVERED;
  this->image_ = Texture::create(cinder::loadImage(
      cinder::app::loadAsset("Images/facingDown.png")));
  this->location_ = location;
}

void Cell::InitCell(int value, Location location) {
  this->value_ = value;
  this->real_value_ = value;
  this->location_ = location;
}

bool Cell::IsSafe() {
  return this->real_value_ >= 0;
}

void Cell::ChangeState(CellState new_state) {
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
      if (this->value_ < 0) {
        this->image_ = Texture::create(
            cinder::loadImage(cinder::app::loadAsset("Images/bomb.png")));
//        this->image_ = Texture::create(
//            cinder::loadImage(cinder::loadUrl("https://images.app.goo.gl/LppZ3YmX2f2h2fm38")));
      } else {
        this->image_ = Texture::create(cinder::loadImage(cinder::app::loadAsset(
            "Images/" + std::to_string(this->value_) + ".png")));
      }
      break;
    }
  }
}

}  // namespace board