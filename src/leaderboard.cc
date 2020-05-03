// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/leaderboard.h>
#include <sqlite_modern_cpp.h>

namespace board {

LeaderBoard::LeaderBoard(const std::string& db_path) : db_{db_path} {
  db_ << "CREATE TABLE if not exists leaderboard (\n"
         "  name   TEXT NOT NULL,\n"
         "  time   INTEGER NOT NULL\n"
         "  id     INTEGER NOT NULL\n"
         "  width  INTEGER NOT NULL\n"
         "  height INTEGER NOT NULL\n"
         "  mines  INTEGER NOT NULL\n"
         ");";
}

//void LeaderBoard::AddScoreToLeaderBoard(const Player& player) {
//  db_ << "insert into leaderboard (name, score) values (?,?);"
//      << player.name
//      << player.score;
//}

}
