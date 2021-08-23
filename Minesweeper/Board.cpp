//
//  Board.cpp
//  Minesweeper
//
//  Created by Alec Kienzle on 8/23/21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
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

void Board::placeMines(int mines)
{
    int minesPlaced = 0;
    srand(time(0));
    
    // Randomly drop the amount of mines determined by the MINES global constant.
    while (minesPlaced < mines)
    {
        int randRow = rand() % 5;
        int randCol = rand() % 5;
        
        if (board[randRow][randCol] != '*')
        {
            board[randRow][randCol] = '*';
            minesPlaced++;
        }
    }
}

char Board::countMines(int y, int x)
{
    char charMines = '-';
    if (isValidCell(y, x))
    {
        int mineCounter = 0;
        if (board[y][x] != '*')
        {
            int north = y-1;
            int south = y+2;
            int west = x-1;
            int east = x+2;
    
            for (int i = north; i < south; i++)
            {
                for (int  j = west; j < east; j++)
                {
                    if (isValidCell(i, j))
                    {
                        if (board[i][j] == '*')
                            mineCounter++;
                    }
                }
                charMines = mineCounter + '0';
            }
        }
    }
    return(charMines);
}

void Board::countAndReveal()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] != '*')
            {
                board[i][j] = countMines(i, j);
            }
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

void Board::chooseCell(int y, int x)
{
    row = y;
    col = x;
}

int Board::getRow() const
{
    return(row);
}

int Board::getCol() const
{
    return(col);
}

char Board::getCellContents(int y, int x) const
{
    return(board[y][x]);
}


bool Board::isValidCell(int y, int x)
{
    bool result = false;
    if ((y >= 0 and y < ROWS) and (x >= 0 and x < COLS))
        result = true;
    
    return(result);
}
