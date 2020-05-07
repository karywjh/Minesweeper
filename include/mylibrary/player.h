// Copyright (c) 2020 [Kary Wang]. All rights reserved.

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

namespace board {

struct Player {
  Player(): name("N/A"), time(0), id(0), width(0), height(0), mines(0){}

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
