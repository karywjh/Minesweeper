// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef FINALPROJECT_LEADERBOARD_H
#define FINALPROJECT_LEADERBOARD_H

#include <sqlite_modern_cpp.h>

#include <string>

namespace board {

class LeaderBoard {
 public:
  explicit LeaderBoard(const std::string& db_path);

  // Adds a player to the leaderboard.
//  void AddScoreToLeaderBoard();

};

}  // namespace board


#endif  // FINALPROJECT_LEADERBOARD_H
