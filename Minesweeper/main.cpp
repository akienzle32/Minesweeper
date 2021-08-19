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
const int MINES = 5;

class Minesweeper
{
private:
    int row;
    int col;
    int mineCounter;
    //bool isAlive;
    
public:
    Minesweeper() : mineCounter(0)
    {}
    
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

    void placeMines(char board[][COLS])
    {
        int minesPlaced = 0;
        srand(time(0));
        
        while (minesPlaced < MINES)
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

    bool isAlive(char board[][COLS])
    {
        bool result = true;
        if (board[row][col] == '*')
            result = false;
        
        return(result);
    }

    void move(char board[][COLS])
    {
        int y, x;
        cout << "Pick a spot on the board (row, column):\n";
        cin >> y; cin >> x;
        
        
        if (isValidCell(y) and isValidCell(x))
        {
            row = y;
            col = x;
    
            if (board[row][col] == '*')
                cout << "You died!" << endl;
            else
                cout << "You're still alive." << endl;
        }
        else
            cout << "Not a valid move!" << endl;
    }
    
    bool isValidCell(int index)
    {
        bool result = true;
        if (index < 0 or index > (ROWS-1))
            result = false;
        
        return(result);
    }

    // Bug for squares that go off board.
    void updateGame(char realBoard[][COLS], char gameBoard[][COLS])
    {
        int north = row-1;
        int south = row+1;
        int east = col+1;
        int west = col-1;
        
        if (realBoard[row][col] == '*')
            gameBoard[row][col] = '*';
        
        else {
            if (isValidCell(north))
            {
                if (realBoard[north][col] == '*')
                    mineCounter++;
            }
            if (isValidCell(south))
            {
                if (realBoard[south][col] == '*')
                    mineCounter++;
            }
            if (isValidCell(east))
            {
                if (realBoard[row][east] == '*')
                    mineCounter++;
            }
            if (isValidCell(west))
            {
                if (realBoard[row][col-1] == '*')
                    mineCounter++;
            }
            if (isValidCell(north) and isValidCell(west))
            {
                if (realBoard[north][west] == '*')
                    mineCounter++;
            }
            if (isValidCell(north) and isValidCell(east))
            {
                if (realBoard[north][east] == '*')
                    mineCounter++;
            }
            if (isValidCell(south) and isValidCell(west))
            {
                if (realBoard[south][west] == '*')
                    mineCounter++;
            }
            if (isValidCell(south) and isValidCell(east))
            {
                if (realBoard[south][east] == '*')
                    mineCounter++;
            }
            
            char charMines = '0' + mineCounter;
            gameBoard[row][col] = charMines;
        }
        mineCounter = 0;
    }
    
    void playGame(char realBoard[][COLS], char gameBoard[][COLS])
    {
        makeBoard(realBoard);
        placeMines(realBoard);
        makeBoard(gameBoard);
        printBoard(gameBoard);
        move(realBoard);
        updateGame(realBoard, gameBoard);
        
        while (isAlive(realBoard))
        {
            printBoard(gameBoard);
            move(realBoard);
            updateGame(realBoard, gameBoard);
        }
        printBoard(gameBoard);
    }
};

int main() {

    Minesweeper game;
    
    char gameBoard[ROWS][COLS];
    char realBoard[ROWS][COLS];
    
    game.makeBoard(gameBoard);
    game.printBoard(gameBoard);
    game.makeBoard(realBoard);
    game.placeMines(realBoard);
    game.printBoard(realBoard);
    game.move(gameBoard);
    game.updateGame(realBoard, gameBoard);
    game.printBoard(gameBoard);
    //game.playGame(realBoard, gameBoard);
    
    
    return(0);
}
