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
const int MINES = 4;

class Minesweeper
{
private:
    int row;
    int col;
    bool cheat; // Setting which enables user to see the realBoard.
    char realBoard[ROWS][COLS]; // Board that contains the locations of all mines. 
    char gameBoard[ROWS][COLS]; // Board that the user sees.
    
public:
    Minesweeper();
    
    void makeBoard(char board[][COLS]);
    
    void placeMines();
    
    char countMines(char board[][COLS], int y, int x);
    
    void countAndReveal(char board[][COLS]);
    
    void printBoard(char board[][COLS]);
    
    bool isAlive();
    
    bool hasWon();
    
    bool isValidCell(int y, int x);

    void move();
    
    void zeroFill(int y, int x);
    
    void updateGame();
    
    void cheatGame();
    
    void playGame();
    
    void testGame();
};

#endif /* Minesweeper_h */
