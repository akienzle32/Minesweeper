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
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            board[i][j] = '-';
        }
    }
}

// Function to print boards. Because an extra digit in the row/column numbers interferes
// with spacing, it treats boards with more than 10 rows/columns differently from those
// with less than 10.
void Board::printBoard()
{
    if (rows < 10)
    {
        std::cout << "   ";
        
        for (int i = 0; i < cols; i++)
        {
            std::cout << i << "  ";
        }
        std::cout << std::endl;
        
        for (int i = 0; i < rows; i++)
        {
            std::cout << i << "  ";
            for (int j = 0; j < cols; j++)
            {
                std::cout << board[i][j] << "  ";
            }
            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << "    ";
    
        for (int i = 0; i < 10; i++)
        {
            std::cout << i << "  ";
        }
        for (int i = 10; i < cols; i++)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    
        for (int i = 0; i < 10; i++)
        {
            std::cout << i << "   ";
            for (int j = 0; j < cols; j++)
            {
                std::cout << board[i][j] << "  ";
            }
        std::cout << std::endl;
        }
        for (int i = 10; i < rows; i++)
        {
            std::cout << i << "  ";
            for (int j = 0; j < cols; j++)
            {
                std::cout << board[i][j] << "  ";
            }
            std::cout << std::endl;
        }
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
    if ((y >= 0 and y < rows) and (x >= 0 and x < cols))
        result = true;
    
    return(result);
}

void Board::setRowAndColSize(int y, int x)
{
    rows = y;
    cols = x;
}

int Board::getRowSize() const
{
    return(rows);
}

int Board::getColSize() const
{
    return(cols);
}
