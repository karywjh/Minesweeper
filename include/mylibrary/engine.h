// Copyright (c) 2020 [Kary Wang]. All rights reserved.

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include "board.h"

namespace board {

enum class GameState {
  kSetting,
  kNotStarted,
  kPlaying,
  kWin,
  kLose,
};

// This is the game engine which is primary way to interact with the game.
class Engine {
 public:
  Engine();

  // Initiate board and game state
  void Init(const int width, const int height, const int mines);

  // Return true if first cell will be opened, and generate board
  bool StartGame(const int row, const int col);

  // If valid opening, change cell image to open,
  // then delete location from board's non_mine_ set
  void OpenCell(const int row, const int col);

  // If right clicked:
  // Covered cell will change to flagged cell
  // Flagged cell will change to covered cell
  void FlagCell(const int row, const int col);

  // Open all mines if player loses
  void OpenAllMines();

  // Change state if player loses or win
  void SetGameState(const int row, const int col);

  void Reset();

  Board GetBoard();
  GameState GetState();

  Board board_;
  GameState state_;
};

}  // namespace board

#endif  // FINALPROJECT_ENGINE_H
