// Copyright (c) 2020 [Kary Wang]. All rights reserved.

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
  db_ << "insert into leaderboard (name, time, id, width, height, mines) "
         "values (?,?,?,?,?,?);"
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

// Includes all players
std::vector<Player> LeaderBoard::RetrieveLeastTimes(const int width,
                                                    const int height,
                                                    const int mines,
                                                    const size_t limit) {
  auto rows = db_ << "select name, time from leaderboard where width=? and "
                     "height=? and mines=? order by time ASC limit ?;"
                  << width
                  << height
                  << mines
                  << limit;
  return GetPlayers(&rows);
}

// Same Player's highest scores
std::vector<Player> LeaderBoard::RetrieveLeastTimes(const Player& player,
                                                    const size_t limit) {
  auto rows =
      db_ << "select name, time from leaderboard where name=? and width=? and "
             "height=? and mines=? order by time ASC limit ?;"
          << player.name
          << player.width
          << player.height
          << player.mines
          << limit;
  return GetPlayers(&rows);
}

std::vector<Player> LeaderBoard::RetrieveLeastTimes(const int id,
                                                    const int width,
                                                    const int height,
                                                    const int mines,
                                                    const size_t limit) {
  auto rows =
      db_ << "select name, time from leaderboard where id=? and width=? and "
             "height=? and mines=? order by time ASC limit ?;"
          << id
          << width
          << height
          << mines
          << limit;
  return GetPlayers(&rows);
}

// Same Player's highest scores
std::vector<Player> LeaderBoard::RetrieveAllTimes(const Player& player) {
  auto rows =
      db_ << "select name, time from leaderboard where name=? and width=? and "
             "height=? and mines=?;"
          << player.name
          << player.width
          << player.height
          << player.mines;
  return GetPlayers(&rows);
}

int LeaderBoard::GetTotalWins(const Player& player) {
  return RetrieveAllTimes(player).size();
}

double LeaderBoard::GetAverageTime(const Player& player) {
  int sum = 0;
  int count = 0;
  std::vector<Player> players = RetrieveAllTimes(player);

  for (const Player& p: players) {
    sum += p.time;
    count++;
  }

  return ((double) (sum * 100 / count)) / 100;
}
}
