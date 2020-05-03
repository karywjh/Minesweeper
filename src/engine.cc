// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/engine.h>

namespace board {

Engine::Engine()
    : board_{Board()}, state_{GameState::kNotStarted} {}


void Engine::Init(const int width, const int height, const int mines) {
  this->board_.InitProperties(width, height, mines);
}


bool Engine::StartGame(const int row, const int col) {
  if (this->board_.cells_[row][col].state_ != board::Cell::CellState::FLAGGED) {
    // Start game when first cell was opened
    this->board_.GenerateBoard(Location(row, col));
    this->state_ = GameState::kPlaying;
    return true;
  }

  return false;
}

void Engine::OpenCell(const int row, const int col) {
  if (this->board_.cells_[row][col].state_ != board::Cell::CellState::FLAGGED) {
    this->board_.cells_[row][col].ChangeState(board::Cell::CellState::OPENED);
    this->board_.non_mine_.erase(Location(row, col));

    // Auto open all neighbors of opened '0' cells
//    this->board_.OpenAllZeroNeighbors();
    this->board_.AutoOpen(Location(row, col), true);

    if (this->board_.IsMine(Location(row, col))) {
      this->state_ = GameState::kLose;
      OpenAllMines();
    }
  }

  if (this->board_.non_mine_.empty()) {
    this->state_ = GameState::kWin;
  }
}

void Engine::FlagCell(const int row, const int col) {
  if (this->board_.cells_[row][col].state_ == board::Cell::CellState::FLAGGED) {
    this->board_.cells_[row][col].ChangeState(board::Cell::CellState::COVERED);
    this->board_.mine_count_++; // Total mine count increased by one

  } else if (this->board_.cells_[row][col].state_ == board::Cell::CellState::COVERED) {
    this->board_.cells_[row][col].ChangeState(board::Cell::CellState::FLAGGED);
    this->board_.mine_count_--; // Total mine count decreased by one
  }
}

void Engine::OpenAllMines() {
  for (Location loc : this->board_.mine_loc_) {
    this->board_.cells_[loc.Row()][loc.Col()].ChangeState(
        board::Cell::CellState::OPENED);
  }
}

Board Engine::GetBoard() {
  return this->board_;
}

GameState Engine::GetState() {
  return this->state_;
}

}  // namespace board
