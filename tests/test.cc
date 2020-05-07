// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <mylibrary/board.h>
#include <mylibrary/engine.h>

using board::Board;
using board::Location;
using board::Cell;
using board::Engine;

/**
 * Test for Board class
 */
TEST_CASE("Board Properties", "[board]") {
  Board board = Board();

  SECTION("Init board") {
    board.InitProperties(2, 3, 4);
    REQUIRE(board.width_ == 2);
    REQUIRE(board.height_ == 3);
    REQUIRE(board.mine_count_ == 4);
    REQUIRE(board.initial_mine_count_ == 4);
  }

  SECTION("Init 2D cells") {
    board.InitProperties(2, 3, 4);
    REQUIRE(board.cells_.size() == 3);
    REQUIRE(board.cells_[0].size() == 2);
  }

  SECTION("Location is mine") {
    board.InitProperties(2, 3, 4);
    board.cells_[0][0].value_ = -1;
    REQUIRE(board.IsMine(Location(0, 0)));
  }
}

TEST_CASE("Generate Cells", "[board]") {
  Board board = Board();
  board.InitProperties(8, 7, 4);

  SECTION("Generate Mines") {
    REQUIRE(board.mine_loc_.empty());
    board.GenerateMines(Location(0, 0));
    REQUIRE(board.mine_loc_.size() == 4);
  }

  // Neighbors of starting position mustn't be a mine
  SECTION("Neighbor not mines") {
    REQUIRE(board.mine_loc_.empty());
    Location start = Location(2, 2);
    board.non_mine_ = board.GetNeighbors(start);
    board.non_mine_.insert(start);

    board.GenerateMines(start);
    for (Location loc: board.GetNeighbors(start)) {
      REQUIRE(board.mine_loc_.find(loc) == board.mine_loc_.end());
    }
  }
}

TEST_CASE("Fill in board", "[board]") {
  Board board = Board();
  board.InitProperties(3, 2, 1);

  SECTION("Fill in non-mine cells' value") {
    // Board should look like this:
    // -1  2  1
    //  2 -1  1
    board.cells_[0][0].InitCell(-1, Location(0, 0));
    board.cells_[1][1].InitCell(-1, Location(1, 1));

    board.FillInValues();

    REQUIRE(board.cells_[0][1].value_ == 2);
    REQUIRE(board.cells_[1][2].value_ == 1);
  }
}

/**
 * Test for Locations
 */
TEST_CASE("Location", "[location]") {
  Board board = Board();
  board.InitProperties(9, 9, 10);

  SECTION("Get neighbors") {
    std::set<Location> locs1 = board.GetNeighbors(Location(0, 0));
    REQUIRE(locs1.size() == 3);

    std::set<Location> locs2 = board.GetNeighbors(Location(3, 2));
    REQUIRE(locs2.size() == 8);
  }

  // Used for adding unique locations in set
  SECTION("Location equal operator") {
    std::set<Location> loc;
    loc.insert(Location(2, 2));
    loc.insert(Location(4, 5));
    loc.insert(Location(2, 2));
    loc.insert(Location(1, 3));
    loc.insert(Location(1, 3));

    REQUIRE(loc.size() == 3);
  }
}

/**
 * Test for Cell class
 */
TEST_CASE("Cell Class", "[cell]") {
  Cell cell = Cell();

  SECTION("Cell initial image") {
    cell.InitCell(-1, Location(0, 0));
    REQUIRE(cell.image_ == "Images/facingDown.png");
    REQUIRE(cell.image_index_ == 9);
  }

  SECTION("Change mine-cell state") {
    cell.InitCell(-1, Location(0, 0));
    cell.ChangeState(Cell::CellState::OPENED);
    REQUIRE(cell.image_ == "Images/bomb.png");
    REQUIRE(cell.image_index_ == 11);
  }

  SECTION("Change non-mine cell state") {
    cell.InitCell(2, Location(0, 0));
    cell.ChangeState(Cell::CellState::OPENED);
    REQUIRE(cell.image_ == "Images/2.png");
    REQUIRE(cell.image_index_ == 2);
  }

  SECTION("Flag cell") {
    cell.InitCell(2, Location(2, 2));
    cell.ChangeState(Cell::CellState::FLAGGED);
    REQUIRE(cell.image_ == "Images/flagged.png");
    REQUIRE(cell.image_index_ == 10);
  }

  SECTION("Flag mine cell") {
    // Flagged a non-mine cell will change real-value of cell to negative number
    cell.InitCell(-1, Location(1, 2));
    cell.ChangeState(Cell::CellState::FLAGGED);
    REQUIRE(cell.image_ == "Images/flagged.png");
    REQUIRE(cell.value_ == -1);
  }
}

// Test for game logics - engine class
TEST_CASE("Engine", "[board][cell]") {
  Engine engine = Engine();
  engine.Init(3, 3, 5);

  SECTION("Start Game") {
    engine.StartGame(0, 0);
    REQUIRE(engine.state_ == board::GameState::kPlaying);
  }

  // Board should look like this:
  //  0  2 -1
  //  2  5 -1
  // -1 -1 -1
  engine.StartGame(0, 0);

  SECTION("Open mine") {
    engine.OpenCell(0, 2);
    REQUIRE(engine.state_ == board::GameState::kLose);
  }

  SECTION("Open non-mine") {
    engine.OpenCell(0, 1);
    REQUIRE(engine.board_.cells_[0][1].image_ == "Images/2.png");
  }

  SECTION("Open zero cell (auto-open neighbors)") {
    engine.OpenCell(0, 0);
    REQUIRE(engine.board_.cells_[0][1].image_ == "Images/2.png");
    REQUIRE(engine.board_.cells_[1][1].image_ == "Images/5.png");
    REQUIRE(engine.state_ == board::GameState::kWin);
  }

  SECTION("Correctly flag mine") {
    engine.FlagCell(2, 0);
    REQUIRE(engine.board_.cells_[2][0].image_ == "Images/flagged.png");
    // Neighbor cell's real value --
    REQUIRE(engine.board_.cells_[1][0].real_value_ == 1);
  }

  SECTION("Fausely flagged mine") {
    engine.FlagCell(1, 0);
    REQUIRE(engine.board_.cells_[1][0].image_ == "Images/flagged.png");
    // Neighbor cell's real value < 0
    REQUIRE(engine.board_.cells_[1][1].real_value_ < 0);
  }

  SECTION("Unflag cell") {
    engine.FlagCell(1, 0);
    REQUIRE(engine.board_.cells_[1][0].image_ == "Images/flagged.png");
    engine.FlagCell(1, 0);
    REQUIRE(engine.board_.cells_[1][0].image_ == "Images/facingDown.png");
  }

  SECTION("Open all mines") {
    engine.OpenAllMines();

    for (Location loc: engine.board_.mine_loc_) {
      REQUIRE(engine.board_.cells_[loc.Row()][loc.Col()].image_ == "Images/bomb.png");
    }
  }
}
