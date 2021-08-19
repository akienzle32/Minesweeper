//
//  main.cpp
//  Minesweeper
//
//  Created by Alec Kienzle on 8/18/21.
//

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

const int ROWS = 5;
const int COLS = 5;
const int MINES = 20;

class Minesweeper
{
private:
    int row;
    int col;
    int mineCounter;
    int moveCounter;
    bool validMove;
    char realBoard[ROWS][COLS];
    char gameBoard[ROWS][COLS];
    
public:
    Minesweeper() : row(0), col(0), mineCounter(0), moveCounter(0), validMove(false)
    {
        makeBoard(realBoard);
        makeBoard(gameBoard);
        placeMines();
    }
    
    void makeBoard(char board[][COLS])
    {
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                board[i][j] = '-';
            }
        }
    }

    void placeMines()
    {
        int minesPlaced = 0;
        srand(time(0));
        
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
    
    void printBoard(char board[][COLS])
    {
        cout << "  ";
        
        for (int i = 0; i < ROWS; i++)
        {
            cout << i << " ";
        }
        cout << endl;
    
        for (int i = 0; i < ROWS; i++)
        {
            cout << i << " ";
            for (int j = 0; j < COLS; j++)
            {
                cout << board[i][j] << " ";
            }
            cout << endl;
            }
    }

    bool isAlive()
    {
        bool result = true;
        if (realBoard[row][col] == '*')
            result = false;
        
        return(result);
    }
    
    bool hasWon()
    {
        bool result = false;
        int moves = ROWS * COLS;
        int neededMoves = moves - MINES;
        
        if (moveCounter == neededMoves)
        {
            result = true;
            cout << "You won!" << endl;
        }
            
        return(result);
    }

    void move(char board[][COLS])
    {
        int y, x;
        cout << "Pick a spot on the board (row, column):\n";
        cin >> y; cin >> x;
        
        if (isValidCell(y, x))
        {
            validMove = true;
            moveCounter++;
            row = y;
            col = x;
        }
        else
        {
            cout << "Not a valid move!" << endl;
        }
    }
    
    bool isValidCell(int y, int x)
    {
        bool result = true;
        if ((y < 0 or y > (ROWS-1) or (x < 0 or x > (COLS-1))))
            result = false;
        
        return(result);
    }
    
    void updateGame()
    {
        if (validMove)
        {
            int north = row-1;
            int south = row+1;
            int east = col+1;
            int west = col-1;
        
            if (realBoard[row][col] == '*')
            {
                gameBoard[row][col] = '*';
                cout << "You died!" << endl;
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
                cout << "You're still alive." << endl;
            }
            mineCounter = 0;
        }
    }
        
    
    void playGame()
    {
        printBoard(gameBoard);
        printBoard(realBoard);
        move(realBoard);
        
        if (validMove)
            updateGame();
        
        while (isAlive() and !hasWon())
        {
            printBoard(gameBoard);
            printBoard(realBoard);
            move(realBoard);
            
            if (validMove)
                updateGame();
        }
        printBoard(realBoard);
    }
};

int main() {

    Minesweeper game;
    
    //char gameBoard[ROWS][COLS];
    //char realBoard[ROWS][COLS];
    /*
    game.makeBoard(gameBoard);
    game.printBoard(gameBoard);
    game.makeBoard(realBoard);
    game.placeMines(realBoard);
    game.printBoard(realBoard);
    game.move(gameBoard);
    game.updateGame(realBoard, gameBoard);
    game.printBoard(gameBoard);
    */
    game.playGame();
    
    
    return(0);
}
