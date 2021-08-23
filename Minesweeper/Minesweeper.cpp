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

Minesweeper::Minesweeper() : row(0), col(0), mineCounter(0), moveCounter(0), revealedCells(0), cheat(true)
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
// and displays this number in the cell.
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

// Probably has bugs with new fill() function.
/*
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
*/

bool Minesweeper::hasWon()
{
    bool result = false;
    int dashCounter = 0;
    int magicNumber = MINES+1;
    
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (gameBoard[i][j] == '-')
                dashCounter++;
        }
    }
    
    if (dashCounter == magicNumber)
    {
        result = true;
        std::cout << "You won!" << std::endl;
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
    
    char digitArray[9] = {'0', '1', '2', '3', '4', '5', '6', '7', '8'};
    
    if (!isValidCell(y, x))
    {
        std::cout << "Not a valid move!" << std::endl;
        move();
    }
    else
    {
        //moveCounter++;
        revealedCells++;
        row = y;
        col = x;
        
        
        for (int i = 0; i < 9; i++)
        {
            if (gameBoard[row][col] == digitArray[i])
            {
                revealedCells--;
                std::cout << "You already chose this cell." << std::endl;
            }
        }
    }
}

void Minesweeper::fill(int y, int x)
{
    if (!isValidCell(y, x))
        return;
    if (realBoard[y][x] != '0')
        return;
    if (gameBoard[y][x] == '0')
        return;
    
    gameBoard[y][x] = '0';
    revealedCells++;
    
    int north = y-1;
    int south = y+1;
    int west = x-1;
    int east = x+1;
    
    fill(north, x);
    fill(south, x);
    fill(y, west);
    fill(y, east);
}

// Function to determine if a cell is on the board.
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
        if (realBoard[row][col] == '*')
        {
            gameBoard[row][col] = '*';
            std::cout << "You died!" << std::endl;
        }
        else if (realBoard[row][col] == '0')
            fill(row, col);
            //Maybe add revealed cells++ here.
        else
        {
            gameBoard[row][col] = countMines(realBoard, row, col);
        }

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

void Minesweeper::testGame()
{
    printBoard(gameBoard);
    printBoard(realBoard);
    //countAndReveal(realBoard);
    //printBoard(realBoard);
}


