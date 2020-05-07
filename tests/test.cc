// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <mylibrary/board.h>

using board::Board;
using cinder::app::App;
using cinder::app::RendererGl;

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
  }
}