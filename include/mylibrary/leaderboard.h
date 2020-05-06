// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef FINALPROJECT_LEADERBOARD_H
#define FINALPROJECT_LEADERBOARD_H

#include <sqlite_modern_cpp.h>
#include "player.h"

#include <string>

namespace board {

class LeaderBoard {
 public:
  explicit LeaderBoard(const std::string& db_path);

  // Adds a player to the leaderboard.
  void AddScoreToLeaderBoard(const Player&);

  // Returns a list of the players with the least times, in increasing order.
  // The size of the list should be no greater than `limit`.
  std::vector<Player> RetrieveLeastTimes(const int width, const int height,
                                              const int mines,
                                              const size_t limit);

  // Returns a list of the players with the least times, in increasing order.
  // that have the same `name` as the input player name.
  std::vector<Player> RetrieveLeastTimes(const Player&, const size_t limit);

  // Returns a list of the players with the least times, in increasing order.
  // that have the same board id.
  std::vector<Player> RetrieveLeastTimes(const int id, const int width,
                                         const int height, const int mines,
                                         const size_t limit);

 private:
  sqlite::database db_;
};

}  // namespace board


#endif  // FINALPROJECT_LEADERBOARD_H
