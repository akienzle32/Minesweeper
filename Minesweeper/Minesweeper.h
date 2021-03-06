//
//  Minesweeper.h
//  Minesweeper
//
//  Created by Alec Kienzle on 8/19/21.
//

#ifndef Minesweeper_h
#define Minesweeper_h
#include "Board.h"

class Minesweeper
{
private:
    int row;
    int col;
    int mines;
    enum Difficulty {EASY, MEDIUM, HARD};
    Board realBoard; // Board that contains the locations of all mines.
    Board gameBoard; // Board that the user sees.
    
public:
    Minesweeper();
    
    void setRowColAndMines(int y, int x, int mines);
    
    void setDifficultyLevel(Difficulty level);
    
    void promptForDifficulty();
    
    void makeBoards();
    
    void placeMines(Board& b);
    
    char countMines(Board& b, int y, int x);
    
    void countAndRevealAllMines(Board& b);
    
    bool isAlive();
    
    bool hasWon();

    void move();
    
    void zeroFill(int y, int x);
    
    void updateGame();
    
    void cheatGame();
    
    void playGame();
    
    void testGame();
};

#endif /* Minesweeper_h */
