// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <CinderImGui.h>
#include <cinder/app/App.h>
#include <cinder/gl/wrapper.h>
#include <cinder/app/Window.h>

namespace myapp {

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::Rectf;

MyApp::MyApp() { }

void MyApp::setup() {
  ImGui::initialize();
  ImGui::SetNextWindowSize(ImVec2(getWindowSize().x, getWindowSize().y));
}

void MyApp::update() { }

void MyApp::draw() {
//   Set Background Color to Black
  cinder::gl::clear(Color(0, 0, 0));

  // Open GUI
  bool open = true;
  if (!ImGui::Begin("Minesweeper", &open))
  {
    ImGui::End();
    return;
  }

  DrawGrid();

//  ImGui::Text("Hello, world!");
//  ui::Text( "Some Bold Title" );
//  ui::ScopedWindow window( "Minesweeper" );
  //  ui::ScopedFont font( "Font-Bold" );
}

void MyApp::keyDown(KeyEvent event) { }

void MyApp::DrawGrid() {
  ImDrawList* draw_list = ImGui::GetWindowDrawList();

  const ImVec2 p = ImVec2(0, 0);
  float x = p.x + 4.0f, y = p.y + 4.0f, spacing = 8.0f;
  static float sz = 36.0f;
  static ImVec4 col = ImVec4(1.0f, 1.0f, 0.4f, 1.0f);
  const ImU32 col32 = ImColor(col);

  draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x+sz, y+sz), col32);
  x += sz;
  y += sz;
  draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x+sz, y+sz), col32);
  ImGui::End();

}

//void MyApp::DrawCell(int x, int y, Tile type) {}

}  // namespace myapp
