// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>

#include <mylibrary/board.h>

namespace myapp {

const int cell_size_ = 30;

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

  void DrawStart();
  void DrawGrid();

  board::Board board_;
  ci::gl::TextureRef image1;
  ci::gl::TextureRef image2;

};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
