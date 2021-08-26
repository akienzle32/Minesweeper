//
//  Board.cpp
//  Minesweeper
//
//  Created by Alec Kienzle on 8/23/21.
//

#include <stdio.h>
#include <iostream>
#include "Board.h"

Board::Board()
{
    makeBoard();
}

void Board::makeBoard()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = '-';
        }
    }
}

void Board::printBoard()
{
    std::cout << "  ";
    
    // Print column numbers first.
    for (int i = 0; i < COLS; i++)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    // Then print row numbers, along with a properly spaced version of the
    // the board.
    for (int i = 0; i < ROWS; i++)
    {
        std::cout << i << " ";
        for (int j = 0; j < COLS; j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

char Board::getCellContents(int y, int x) const
{
    return(board[y][x]);
}

void Board::setCellContents(int y, int x, char c)
{
    board[y][x] = c;
}


bool Board::isValidCell(int y, int x)
{
    bool result = false;
    if ((y >= 0 and y < ROWS) and (x >= 0 and x < COLS))
        result = true;
    
    return(result);
}
