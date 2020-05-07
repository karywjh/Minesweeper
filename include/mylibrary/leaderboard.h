// Copyright (c) 2020 [Kary Wang]. All rights reserved.

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
  void AddScoreToLeaderBoard(const Player& player);

  // Returns a list of the players with the least times, in increasing order.
  // The size of the list should be no greater than `limit`.
  std::vector<Player> RetrieveLeastTimes(const int width, const int height,
                                              const int mines,
                                              const size_t limit);

  // Returns a list of the players with the least times, in increasing order.
  // that have the same `name` as the input player name.
  std::vector<Player> RetrieveLeastTimes(const Player& player,
                                         const size_t limit);

  // Returns a list of the players with the least times, in increasing order.
  // that have the same board id.
  std::vector<Player> RetrieveLeastTimes(const int id, const int width,
                                         const int height, const int mines,
                                         const size_t limit);

  // Retrieve all times that the player has.
  std::vector<Player> RetrieveAllTimes(const Player& player);

  // Total number of games played by this player
  int GetTotalWins(const Player& player);

  // Get average time of current player with 2 decimal points
  double GetAverageTime(const Player& player);

 private:
  sqlite::database db_;
};

}  // namespace board


#endif  // FINALPROJECT_LEADERBOARD_H
