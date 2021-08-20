//
//  Minesweeper.h
//  Minesweeper
//
//  Created by Alec Kienzle on 8/19/21.
//

#ifndef Minesweeper_h
#define Minesweeper_h

const int ROWS = 5;
const int COLS = 5;
const int MINES = 7;

class Minesweeper
{
private:
    int row;
    int col;
    int mineCounter;
    int moveCounter;
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
    
    void printBoard(char board[][COLS]);

    void move();
    
    void updateGame();
    
    void cheatGame();
    
    void playGame();
};

#endif /* Minesweeper_h */
