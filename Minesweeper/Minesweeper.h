//
//  Minesweeper.h
//  Minesweeper
//
//  Created by Alec Kienzle on 8/19/21.
//

#ifndef Minesweeper_h
#define Minesweeper_h
#include "Board.h"

const int MINES = 20;

class Minesweeper
{
private:
    int row_size;
    int col_size;
    int row;
    int col;
    Board realBoard; // Board that contains the locations of all mines.
    Board gameBoard; // Board that the user sees.
    
public:
    Minesweeper();
    
    void setRowAndColSizes(int y, int x);
    
    void makeBoards();
    
    void placeMines();
    
    char countMines(Board& b, int y, int x);
    
    void countAndReveal();
    
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
