# Final Project - Minesweeper

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.

**Author**: Kary Wang - [`jiahuiw4@illinois.edu`](mailto:jiahuiw4@illinois.edu)

---

## Project Summary ##
This project implements the minesweeper game. Specifically, it generates a minesweeper board. Make a GUI to display the puzzle and allows user to play it. <sup id="a1">[1](#f1)</sup>

#### Motivation ####
Minesweeper is one of my favorite games of all time. Knowing that there's some small tricks on solving it, I wanted to implement the game and also try to write a solver for it. Writing it myself, I'm also able to make interesting modes and levels such as making a no-flags mode that disallowed player to solve the puzzle without marking any flags. 

## Functionalities ##

* **Levels:** Beginner, Intermediate, Advanced
      
* **Player's Move:** Click to open cells. Right click to mark mines.

* **Scoreboard:** Score Board that keep tracks of time, best time, average time, win percentage, total wins...<sup id="a2">[2](#f2)</sup>

#### Additional Goals ####

* **Hint:** In hint mode, highlight the safe cells that are not mines for sure.

* **Solver:** Write a solver to solve the minesweeper puzzle.

* **NF (No Flags):** Disabled players to mark flags.

* **Auto-open:** Click on a already-opened cell with all mines correctly flagged around it will open up cells adjacent to it that's safe. 

## Timeline ##
* **Week 1:** 
  - Wrote implementations to generate boards of the puzzle.

* **Week 2:**
  - Make GUI for the game. (player can click to mark cells, select game mode, etc.)

* **Week 3:**
  - Enhance on week 1 & 2's work, make board and GUI compatible for all levels. 

  - Use SQLite to make database to record scores.

* **Week 4:** 
  - Implement additional functionalities like Hinter and Solver. 
  

<b id="f1">1</b> Using Cinder to display the graphics. https://libcinder.org/docs/reference/index.html [↩](#a1)

<b id="f2">2</b> Using SQLite and SqliteModernCpp. https://www.sqlitetutorial.net/ and https://github.com/SqliteModernCpp/sqlite_modern_cpp/tree/dev [↩](#a2)
