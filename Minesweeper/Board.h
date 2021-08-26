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
    char board[ROWS][COLS];
    
public:
    Board();
    
    void makeBoard();
    
    void printBoard();
    
    char getCellContents(int y, int x) const;
    
    void setCellContents(int y, int x, char c);
    
    bool isValidCell(int y, int x);

};
#endif /* Board_h */
