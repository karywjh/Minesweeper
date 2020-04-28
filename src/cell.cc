// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/cell.h>
#include <cinder/app/App.h>

namespace board {

Cell::Cell(int value) {
    this->value_ = value;
    this->state_ = CellState::COVERED;
    this->image_ = ci::gl::Texture::create(cinder::loadImage(
        cinder::app::loadAsset("Images/" + std::to_string(value) + ".png")));
}

}  // namespace board