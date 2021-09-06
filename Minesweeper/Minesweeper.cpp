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
    promptForDifficulty();
    makeBoards();
}

void Minesweeper::setRowColAndMines(int y, int x, int mines)
{
    realBoard.setRowAndColSize(y, x);
    gameBoard.setRowAndColSize(y, x);
    this->mines = mines;

}

void Minesweeper::promptForDifficulty()
{
    char c;
    std::cout << "Please choose a level of difficulty.\n";
    std::cout << "Enter 'E' for easy (8x8 board), 'M' for medium (16x16 board),\nor 'H' for hard (16x20 board):\n\n";
    
    std::cin >> c;
    switch(c)
    {
        case 'E':
            setDifficultyLevel(EASY);
            break;
        case 'M':
            setDifficultyLevel(MEDIUM);
            break;
        case 'H':
            setDifficultyLevel(HARD);
            break;
        default:
            std::cout << "That's not a valid level of difficulty.\n\n";
            promptForDifficulty();
    }
}

void Minesweeper::setDifficultyLevel(Difficulty level)
{
    switch(level)
    {
        case EASY:
            setRowColAndMines(8, 8, 10);
            break;
        case MEDIUM:
            setRowColAndMines(16, 16, 40);
            break;
        case HARD:
            setRowColAndMines(16, 20, 65);
            break;
    }
}

// Helper function to create both boards.
void Minesweeper::makeBoards()
{
    gameBoard.makeBoard();
    realBoard.makeBoard();
    placeMines(realBoard);
    countAndRevealAllMines(realBoard);
}

void Minesweeper::placeMines(Board& b)
{
    int minesPlaced = 0;
    srand(time(0));
    
    // Randomly drop the amount of mines determined by the MINES global constant.
    while (minesPlaced < mines)
    {
        int randRow = rand() % b.getRowSize();
        int randCol = rand() % b.getColSize();
        
        if (b.getCellContents(randRow, randCol) != '*')
        {
            b.setCellContents(randRow, randCol, '*');
            minesPlaced++;
        }
    }
}

// Counts all mines immediately adjacent to a given cell.
char Minesweeper::countMines(Board& b, int y, int x)
{
    char charMines = '-';
    if (b.isValidCell(y, x))
    {
        int mineCounter = 0;
        if (b.getCellContents(y, x) != '*')
        {
            int north = y-1;
            int south = y+2;
            int west = x-1;
            int east = x+2;
    
            for (int i = north; i < south; i++)
            {
                for (int  j = west; j < east; j++)
                {
                    if (b.isValidCell(i, j))
                    {
                        if (b.getCellContents(i, j) == '*')
                            mineCounter++;
                    }
                }
                charMines = mineCounter + '0';
            }
        }
    }
    return(charMines);
}

// This function applies countMines() to every cell on the board.
void Minesweeper::countAndRevealAllMines(Board& b)
{
    for (int i = 0; i < b.getRowSize(); i++)
    {
        for (int j = 0; j < b.getColSize(); j++)
        {
            if (b.getCellContents(i, j) != '*')
                b.setCellContents(i, j, countMines(b, i, j));
        }
    }
}

bool Minesweeper::isAlive()
{
    bool result = true;
    if (gameBoard.getCellContents(row, col) == '*')
    {
        result = false;
        realBoard.printBoard();
        std::cout << "You died!" << std::endl;
    }
    
    return(result);
}

// Determines if the player has won the game by calculating if the number of
// unrevealed cells on gameBoard is equal to the number of mines.
bool Minesweeper::hasWon()
{
    bool result = false;
    int dashCounter = 0;
    
    for (int i = 0; i < gameBoard.getRowSize(); i++)
    {
        for (int j = 0; j < gameBoard.getColSize(); j++)
        {
            if (gameBoard.getCellContents(i, j) == '-')
                dashCounter++;
        }
    }
    
    if (dashCounter == mines)
    {
        result = true;
        realBoard.printBoard();
        std::cout << "You won!" << std::endl;
    }
    
    return(result);
}

// Sets row and column variables to values determined by the player (if the values are
// valid based on the size of rows and cols in the Board class). The function accepts
// these values as standard x,y coordinates (i.e., column first, then row). It also
// informs the player if they have already selected this cell before.
void Minesweeper::move()
{
    int y, x;
    std::cout << "Pick a spot on the board (row, column):\n";
    std::cin >> y; std::cin >> x;
    
    char digitArray[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
    
    if (!gameBoard.isValidCell(y, x))
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
            if (gameBoard.getCellContents(row, col) == digitArray[i])
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
    if (!realBoard.isValidCell(y, x))
        return;
    if (realBoard.getCellContents(y, x) != '0')
        return;
    if (gameBoard.getCellContents(y, x) == '0')
        return;
    
    gameBoard.setCellContents(y, x, '0');
    
    int north = y-1;
    int south = y+1;
    int west = x-1;
    int east = x+1;
    
    zeroFill(north, x);
    zeroFill(south, x);
    zeroFill(y, west);
    zeroFill(y, east);
}

// This function updates the gameBoard appropriately based on the user's choice of cell.
void Minesweeper::updateGame()
{
    if (realBoard.getCellContents(row, col) == '*')
        gameBoard.setCellContents(row, col, '*');
        
    else if (realBoard.getCellContents(row, col) == '0')
        zeroFill(row, col);
        
    else
        gameBoard.setCellContents(row, col, countMines(realBoard, row, col));
}

// Allows the user to cheat by displaying the realBoard (i.e., the one with the mines).
void Minesweeper::cheatGame()
{
    realBoard.printBoard();
}

// Recursive function that drives gameplay. 
void Minesweeper::playGame()
{
    if (!isAlive())
        return;
    if (hasWon())
        return;

    gameBoard.printBoard();
    move();
    updateGame();
    playGame();
}

// Utility function employed purely for testing purposes. 
void Minesweeper::testGame()
{
    gameBoard.printBoard();
    realBoard.printBoard();
    move();
    updateGame();
    gameBoard.printBoard();
    move();
    gameBoard.printBoard();
    updateGame();
}


