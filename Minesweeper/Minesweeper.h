//
//  Minesweeper.h
//  Minesweeper
//
//  Created by Alec Kienzle on 8/19/21.
//

#ifndef Minesweeper_h
#define Minesweeper_h

const int ROWS = 3;
const int COLS = 3;
const int MINES = 1;

class Minesweeper
{
private:
    int row;
    int col;
    int mineCounter;
    int moveCounter;
    int revealedCells;
    bool cheat;
    char realBoard[ROWS][COLS];
    char gameBoard[ROWS][COLS];
    
public:
    Minesweeper();
    
    bool isValidCell(int y, int x);
    
    bool isAlive();
    
    bool hasWon();
    
    void makeBoard(char board[][COLS]);

    void placeMines();
    
    char countMines(char board[][COLS], int y, int x);
    
    void countAndReveal(char board[][COLS]);
    
    void printBoard(char board[][COLS]);

    void move();
    
    void fill(int y, int x);
    
    void updateGame();
    
    void cheatGame();
    
    void playGame();
    
    void testGame();
};

#endif /* Minesweeper_h */
