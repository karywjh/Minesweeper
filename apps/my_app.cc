// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/Window.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/wrapper.h>
#include <cinder/gl/gl.h>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::Rectf;

MyApp::MyApp() : board_{board::Board()} {}

void MyApp::setup() {
  image1 = ci::gl::Texture::create(cinder::loadImage(cinder::app::loadAsset("Images/0.png")));
  image2 = ci::gl::Texture::create(cinder::loadImage(cinder::app::loadAsset("Images/1.png")));
}

void MyApp::update() {
}

void MyApp::draw() {
//   Set Background Color to Black
  cinder::gl::clear(Color(0, 0, 0));

  DrawStart();
  DrawGrid();
}

void MyApp::keyDown(KeyEvent event) { }

void MyApp::DrawStart(){
  // Letting User to Select Settings for Game
  // Initiate board_
  board_.InitProperties(16, 16, 40); // test code
  board::Cell** cells = board_.GenerateBoard(16, 16, 40, board::Position{0, 0});
}

void MyApp::DrawGrid() {
  // Change the window size depending on the board size.
  setWindowSize(board_.width_ * cell_size_, board_.height_ * cell_size_);

  // Loop through every cell of board, draw Grid
  cinder::gl::draw(image1, cinder::Rectf(0, 0, cell_size_, cell_size_));

  cinder::Rectf rectf(cell_size_, 0, cell_size_ + 30,  cell_size_);
  cinder::gl::draw(image2, rectf);
}

}  // namespace myapp
