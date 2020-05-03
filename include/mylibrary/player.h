// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

namespace board {

struct Player {
  Player(const std::string& name, int time, int id, int width, int height,
         int mines)
      : name(name), time(time), id(id), width(width), height(height), mines(mines) {}

  std::string name;
  int time;
  int id;
  int width;
  int height;
  int mines;
};

}  // namespace board

#endif  // FINALPROJECT_PLAYER_H
