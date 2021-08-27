//
//  Board.h
//  Minesweeper
//
//  Created by Alec Kienzle on 8/23/21.
//

#ifndef Board_h
#define Board_h

const int MAX_ROWS = 16;
const int MAX_COLS = 30;

class Board
{
private:
    char board[MAX_COLS][MAX_ROWS];
    int rows;
    int cols;
    
public:
    Board();
    
    void makeBoard();
    
    void printBoard();
    
    char getCellContents(int y, int x) const;
    
    void setCellContents(int y, int x, char c);
    
    bool isValidCell(int y, int x);
    
    void setRowAndColSize (int y, int x);
    
    int getRowSize() const;
    
    int getColSize() const;

};
#endif /* Board_h */
