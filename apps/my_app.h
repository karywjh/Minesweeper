// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>

#include <mylibrary/engine.h>
#include <mylibrary/leaderboard.h>

namespace myapp {

using board::Engine;

const int kCellSize_ = 30;

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown(cinder::app::MouseEvent) override;
  void ResetGame();
  void DrawStart();
  void DrawGrid();
  void DrawLose();
  void DrawWin();

 private:
  Engine engine_;
  board::LeaderBoard leaderboard_;
  std::vector<board::Player> top_overall_players_;
  std::vector<board::Player> top_id_players_;

  std::chrono::time_point<std::chrono::system_clock> start_time_;
  int game_time_;
  bool update_scores_;
  std::string name_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
