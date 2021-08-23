//
//  Board.h
//  Minesweeper
//
//  Created by Alec Kienzle on 8/23/21.
//

#ifndef Board_h
#define Board_h

const int ROWS = 5;
const int COLS = 5;

class Board
{
private:
    int row;
    int col;
    char board[ROWS][COLS];
    
public:
    Board();
    
    void makeBoard();

    void placeMines(int mines);
    
    char countMines(int y, int x);
    
    void printBoard();
    
    void countAndReveal();
    
    void chooseCell(int y, int x);
    
    int getRow() const;
    
    int getCol() const;
    
    char getCellContents(int y, int x) const;
    
    bool isValidCell(int y, int x);

};
#endif /* Board_h */
