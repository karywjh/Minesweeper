// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/engine.h>

namespace board {

Engine::Engine()
    : board_{Board()}, state_{GameState::kSetting} {}


void Engine::Init(const int width, const int height, const int mines) {
  this->board_.InitProperties(width, height, mines);
}

bool Engine::StartGame(const int row, const int col) {
  if (this->board_.cells_[row][col].state_ != Cell::CellState::FLAGGED) {
    // Start game when first cell was opened
    this->board_.GenerateBoard(Location(row, col));
    this->state_ = GameState::kPlaying;

    return true;
  }

  return false;
}

void Engine::OpenCell(const int row, const int col) {
  if (this->board_.cells_[row][col].state_ == Cell::CellState::COVERED) {
    // Clicking action to open covered cells
    this->board_.cells_[row][col].ChangeState(Cell::CellState::OPENED);
    this->board_.non_mine_.erase(Location(row, col));

    // Auto open all neighbors of opened '0' cells
    this->board_.OpenZeroNeighbors(Location(row, col));

  } else if (this->board_.cells_[row][col].state_ == Cell::CellState::OPENED) {
    // Open neighbors if all mines around it is correctly flagged
    this->board_.OpenNeighbors(Location(row, col));
  }

  SetGameState(row, col);
}

void Engine::FlagCell(const int row, const int col) {
  if (this->board_.cells_[row][col].state_ == Cell::CellState::FLAGGED) {
    this->board_.cells_[row][col].ChangeState(Cell::CellState::COVERED);
    this->board_.mine_count_++;  // Total mine count increased by one

    this->board_.UpdateNeighbor(Location(row, col), false);

  } else if (this->board_.cells_[row][col].state_ == Cell::CellState::COVERED) {
    this->board_.cells_[row][col].ChangeState(Cell::CellState::FLAGGED);
    this->board_.mine_count_--;  // Total mine count decreased by one

    this->board_.UpdateNeighbor(Location(row, col), true);
  }
}

void Engine::OpenAllMines() {
  for (Location loc : this->board_.mine_loc_) {
    this->board_.cells_[loc.Row()][loc.Col()].ChangeState(Cell::CellState::OPENED);
  }
}

void Engine::SetGameState(const int row, const int col) {
  // Check if player loses
  if (!this->board_.cells_[row][col].IsSafe()) {
    this->state_ = GameState::kLose;
  }

  // Check if player wins
  if (this->board_.non_mine_.empty()) {
    this->state_ = GameState::kWin;
  }
}

void Engine::Reset() {
  this->board_ = Board();
  this->state_ = GameState::kNotStarted;
}

Board Engine::GetBoard() {
  return this->board_;
}

GameState Engine::GetState() {
  return this->state_;
}

}  // namespace board
