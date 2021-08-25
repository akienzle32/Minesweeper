//
//  Minesweeper.cpp
//  Minesweeper
//
//  Created by Alec Kienzle on 8/19/21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "Minesweeper.h"

Minesweeper::Minesweeper() : row(0), col(0)
{
    makeBoard(realBoard);
    makeBoard(gameBoard);
    placeMines();
    countAndReveal(realBoard);
}

void Minesweeper::makeBoard(char board[][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = '-';
        }
    }
}

// Function to drop the requisite number of mines randomly across the board.
void Minesweeper::placeMines()
{
    int minesPlaced = 0;
    srand(time(0));
    
    // Randomly drop the amount of mines determined by the MINES global constant.
    while (minesPlaced < MINES)
    {
        int randRow = rand() % ROWS;
        int randCol = rand() % COLS;
        
        if (realBoard[randRow][randCol] != '*')
        {
            realBoard[randRow][randCol] = '*';
            minesPlaced++;
        }
    }
}

// This function counts all the mines immediately adjacent to a given cell,
// and returns this number as a character.
char Minesweeper::countMines(char board[][COLS], int y, int x)
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

// This function counts all the adjacent mines to every cell on the board
// and displays this number in the cell. Within normal gameplay, it is only called on
// the realBoard.
void Minesweeper::countAndReveal(char board[][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] != '*')
            {
                board[i][j] = countMines(board, i, j);
            }
        }
    }
}

void Minesweeper::printBoard(char board[][COLS])
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

bool Minesweeper::isAlive()
{
    bool result = true;
    
    if (gameBoard[row][col] == '*')
    {
        result = false;
        printBoard(realBoard);
        std::cout << "You died!" << std::endl;
    }
    
    return(result);
}

// This function determines if the player has won the game by determining if the number of
// revealed cells is equal to the number of cells without mines.
bool Minesweeper::hasWon()
{
    bool result = false;
    int dashCounter = 0;
    int magicNumber = MINES;
    
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (gameBoard[i][j] == '-')
                dashCounter++;
        }
    }
    
    if (dashCounter == magicNumber and realBoard[row][col] != '*')
    {
        result = true;
        printBoard(realBoard);
        std::cout << "You won!" << std::endl;
    }
    
    return(result);
}

// Function to determine if a cell is on the board.
bool Minesweeper::isValidCell(int y, int x)
{
    bool result = false;
    
    if ((y >= 0 and y < ROWS) and (x >= 0 and x < COLS))
        result = true;
    
    return(result);
}

// Set row and column variables to values determined by the player (if the values
// are valid based on the size of the rows and columns). The function allows the user
// to input these values as standard x,y coordinates (i.e., column first, then row). 
void Minesweeper::move()
{
    int y, x;
    std::cout << "Pick a spot on the board (row, column):\n";
    std::cin >> y; std::cin >> x;
    
    char digitArray[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
    
    if (!isValidCell(y, x))
    {
        std::cout << "Not a valid move!" << std::endl;
        move();
    }
    else
    {
        row = x;
        col = y;
        
        for (int i = 0; i < 9; i++)
        {
            if (gameBoard[row][col] == digitArray[i])
            {
                std::cout << "You already revealed this cell." << std::endl;
            }
        }
    }
}

// Recursive "floodfill" function to show the user all connecting cells bordered by zero
// mines if they have selected a cell bordered by zero mines.
void Minesweeper::zeroFill(int y, int x)
{
    if (!isValidCell(y, x))
        return;
    if (realBoard[y][x] != '0')
        return;
    if (gameBoard[y][x] == '0')
        return;
    
    gameBoard[y][x] = '0';
    
    int north = y-1;
    int south = y+1;
    int west = x-1;
    int east = x+1;
    
    zeroFill(north, x);
    zeroFill(south, x);
    zeroFill(y, west);
    zeroFill(y, east);
}

// This function updates the game appropriately based on the user's choice of cell.
void Minesweeper::updateGame()
{
    if (realBoard[row][col] == '*')
        gameBoard[row][col] = '*';
        
    else if (realBoard[row][col] == '0')
        zeroFill(row, col);
        
    else
        gameBoard[row][col] = countMines(realBoard, row, col);
}

void Minesweeper::cheatGame()
{
    printBoard(realBoard);
}

void Minesweeper::playGame()
{
    if (!isAlive())
        return;
    if (hasWon())
        return;
    
    printBoard(gameBoard);
    move();
    updateGame();
    playGame();
}

// Utility function employed purely for testing purposes. 
void Minesweeper::testGame()
{
    printBoard(gameBoard);
    printBoard(realBoard);
    //countAndReveal(realBoard);
    //printBoard(realBoard);
}


