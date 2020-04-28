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

MyApp::MyApp() { }

void MyApp::setup() {
  image1 = ci::gl::Texture::create(cinder::loadImage(cinder::app::loadAsset("Images/0.png")));
  image2 = ci::gl::Texture::create(cinder::loadImage(cinder::app::loadAsset("Images/1.png")));

}

void MyApp::update() {
}

void MyApp::draw() {
//   Set Background Color to Black
  cinder::gl::clear(Color(0, 0, 0));

  board::Board b(board::Position{0, 0});
  DrawGrid(b);
}

void MyApp::keyDown(KeyEvent event) { }

void MyApp::DrawGrid(const board::Board& board) {
  cinder::gl::draw(image1, cinder::Rectf(0, 0, cell_size_, cell_size_));

  cinder::Rectf rectf(cell_size_, 0, cell_size_ + 30,  cell_size_);
  cinder::gl::draw(image2, rectf);
//  , cinder::vec2(20.0f, 20.0f)
}

//void MyApp::DrawCell(int x, int y, Tile type) {}

}  // namespace myapp
