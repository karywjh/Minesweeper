// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/leaderboard.h>
#include <sqlite_modern_cpp.h>

namespace board {

LeaderBoard::LeaderBoard(const std::string& db_path) : db_{db_path} {
//  sqlite::database db_(db_path);
  db_ << "create table if not exists leaderboard (\n"
           "  name TEXT NOT NULL,\n"
           "  time INTEGER NOT NULL,\n"
           "  id INTEGER NOT NULL,\n"
           "  width INTEGER NOT NULL,\n"
           "  height INTEGER NOT NULL,\n"
           "  mines INTEGER NOT NULL\n"
           ");";
}

void LeaderBoard::AddScoreToLeaderBoard(const Player& player) {
  db_ << "insert into leaderboard (name, time, id, width, height, mines) values (?,?,?,?,?,?);"
      << player.name
      << player.time
      << player.id
      << player.width
      << player.height
      << player.mines;
}

std::vector<Player> GetPlayers(sqlite::database_binder* rows) {
  std::vector<Player> players;

  for (auto&& row : *rows) {
    std::string name;
    int time;
    int id;
    int width;
    int height;
    int mines;

    row >> name >> time >> id >> width >> height >> mines;
    Player player = {name, time, id, width, height, mines};
    players.push_back(player);
  }

  return players;
}

std::vector<Player> LeaderBoard::RetrieveLeastTimes(const size_t limit) {
  auto rows = db_ << "select name, time from leaderboard order by time ASC limit ?;"
                  << limit;
  return GetPlayers(&rows);
}

std::vector<Player> LeaderBoard::RetrieveLeastTimes(const Player& player,
                                               const size_t limit) {
  auto rows = db_ << "select name, time from leaderboard where name=? order by time ASC limit ?;"
                  << player.name
                  << limit;
  return GetPlayers(&rows);
}

}
