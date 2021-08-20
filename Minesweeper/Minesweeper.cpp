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

Minesweeper::Minesweeper() : row(0), col(0), mineCounter(0), moveCounter(0), cheat(true)
{
    makeBoard(realBoard);
    makeBoard(gameBoard);
    placeMines();
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

void Minesweeper::placeMines()
{
    int minesPlaced = 0;
    srand(time(0));
    
    // Randomly drop the amount of mines determined by the MINES global constant.
    while (minesPlaced < MINES)
    {
        int randRow = rand() % 5;
        int randCol = rand() % 5;
        
        if (realBoard[randRow][randCol] != '*')
        {
            realBoard[randRow][randCol] = '*';
            minesPlaced++;
        }
    }
}

void Minesweeper::printBoard(char board[][COLS])
{
    std::cout << "  ";
    
    // Print column numbers first.
    for (int i = 0; i < ROWS; i++)
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
    if (realBoard[row][col] == '*')
        result = false;
    
    return(result);
}

// This function determines if the player has won by subtracting the amount of mines on the
// board from the amount of moves made thus far. If the player has made this requisite
// number of valid moves without dying, then they win.
bool Minesweeper::hasWon()
{
    bool result = false;
    int moves = ROWS * COLS;
    int neededMoves = moves - MINES;
    
    if (moveCounter == neededMoves and realBoard[row][col] != '*')
    {
        result = true;
    }
        
    return(result);
}

// Set row and column variables to values determined by the player (if the values
// are valid based on the size of the rows and columns).
void Minesweeper::move()
{
    int y, x;
    std::cout << "Pick a spot on the board (row, column):\n";
    std::cin >> y; std::cin >> x;
    
    if (!isValidCell(y, x))
    {
        std::cout << "Not a valid move!" << std::endl;
        move();
    }
    else
    {
        moveCounter++;
        row = y;
        col = x;
    }
}

bool Minesweeper::isValidCell(int y, int x)
{
    bool result = false;
    if ((y >= 0 and y < ROWS) and (x >= 0 and x < COLS))
        result = true;
    
    return(result);
}

// This function counts the number of adjacent mines to the selected cell and
// displays that number in the selected cell. It also prints messages if the player
// has either won or lost.
void Minesweeper::updateGame()
{
    if (!hasWon())
    {
        int north = row-1;
        int south = row+1;
        int east = col+1;
        int west = col-1;
    
        if (realBoard[row][col] == '*')
        {
            gameBoard[row][col] = '*';
            std::cout << "You died!" << std::endl;
        }
        else {
            if (isValidCell(north, col))
            {
                if (realBoard[north][col] == '*')
                    mineCounter++;
            }
            if (isValidCell(south, col))
            {
                if (realBoard[south][col] == '*')
                    mineCounter++;
            }
            if (isValidCell(row, east))
            {
                if (realBoard[row][east] == '*')
                    mineCounter++;
            }
            if (isValidCell(row, west))
            {
                if (realBoard[row][col-1] == '*')
                    mineCounter++;
            }
            if (isValidCell(north, west))
            {
                if (realBoard[north][west] == '*')
                    mineCounter++;
            }
            if (isValidCell(north, east))
            {
                if (realBoard[north][east] == '*')
                    mineCounter++;
            }
            if (isValidCell(south, west))
            {
                if (realBoard[south][west] == '*')
                    mineCounter++;
            }
            if (isValidCell(south, east))
            {
                if (realBoard[south][east] == '*')
                    mineCounter++;
            }
        
            char charMines = '0' + mineCounter;
            gameBoard[row][col] = charMines;
        }
        mineCounter = 0;
    }
    else
        std::cout << "You won!" << std::endl;
}

// This function allows the user to cheat by displaying the realBoard (i.e., the
// one with the mines in it) once at the beginning of the game. This setting can be
// changed simply by switching the boolean cheat variable in the Minesweeper
// constructor.
void Minesweeper::cheatGame()
{
    if (cheat)
        printBoard(realBoard);
}

void Minesweeper::playGame()
{
    printBoard(gameBoard);
    cheatGame();
    move();
    
    // Continue playing as long as the player is alive and has not won yet.
    while (isAlive() and !hasWon())
    {
        updateGame();
        printBoard(gameBoard);
        std::cout << "You're still alive." << std::endl;
        move();
    }
    printBoard(realBoard);
    updateGame();
}
