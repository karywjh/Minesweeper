# Development

---

## Goals

- Game Logic:
    - [x] Board class
        - [x] Generate Puzzle
        - [x] Keep track of board state
    - [x] Cell class
        - [x] Store images and values
        - [x] Change image after player's move
    - [ ] Engine class
        
- UI:
    - [ ] Draw starting UI, where user can choose board difficulties
    - [x] Draw Board
    - [x] Mouse Clicking Functionality (click, right click) 
    - [ ] Top bar to display game info
        - [ ] Time and mines left
        - [ ] "New" game button, setting button
    - [ ] Update board after player's move
    - [ ] Ending UI if player wins/loses
    
- Database:
    - [ ] Display time and score by username after game ends
        - [ ] Time, Best time, Average time, win percentage, games played, games won and etc. 
    - [ ] Display scores for board with same id
    
- Additional
    - [ ] auto-opening
        - [ ] click on opened cells to auto-open neighbors
    - [ ] Play board by ID
    - [ ] 3D Board
    
### Week 1
* **April 19:** 
    - researched about cinder block
   
* **April 20:** 
    - researched about ImGui
    - set up ImGui cinder block in cmake
    
* **April 21:** 
    - wrote outline for board and cell classes
    - able to drew shapes on GUI using ImGui
    
* **April 22 - 25:**
    - continue to read documents about ImGui to display images

### Week 2

* **April 26:** 
    - researched about libraries to store and display images
    - switched to using cinder and openGL
    
* **April 27:**
    - Store images in Cell
    - display images at given position on Gui
 
* **April 28:**
    - switch image if player changed cell states
    - made vector and set of Cells for board
 
* **April 29:**
    - generate mines
    - draw initial board
    - fill in values
    - generate full board
    - open / flag / unflag functionality
  
* **April 30:**
    - made Engine class
    - made and draw basic end game ui and logic
