//
//  main.cpp
//  Minesweeper
//
//  Created by Alec Kienzle on 8/18/21.
//

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int ROWS = 5;
const int COLS = 5;

class Minesweeper
{
private:
    int row;
    int col;
    int mineCounter;
    
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
        board[0][3] = '*';
        board[2][1] = '*';
        board[3][2] = '*';
        board[4][3] = '*';
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
        int i, j;
        cout << "Pick a spot on the board (row, column):\n";
        cin >> i; cin >> j;
        
        if (i < ROWS and j < COLS){
            row = i;
            col = j;
            
            if (board[row][col] == '*')
                cout << "You died!" << endl;
            else
                cout << "You're still alive." << endl;
        }
        else
            cout << "Not a valid move!" << endl;
    
    }

    void updateBoard(char realBoard[][COLS], char gameBoard[][COLS])
    {
        if (realBoard[row][col] == '*')
            gameBoard[row][col] = '*';
        else {
            if (realBoard[row-1][col] == '*')
                mineCounter++;
            if (realBoard[row+1][col] == '*')
                mineCounter++;
            if (realBoard[row][col-1] == '*')
                mineCounter++;
            if (realBoard[row][col+1] == '*')
                mineCounter++;
            char charMines = '0' + mineCounter;
            gameBoard[row][col] = charMines;
        }
        mineCounter = 0;
    }
    
    void playGame(char realBoard[][COLS], char gameBoard[][COLS])
    {
        move(realBoard);
        
        while (isAlive(realBoard))
        {
            move(realBoard);
            updateBoard(realBoard, gameBoard);
            printBoard(gameBoard);
        }
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
    cout << endl;
    
    game.playGame(realBoard, gameBoard);
    
    return(0);
}
