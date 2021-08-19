//
//  main.cpp
//  Minesweeper
//
//  Created by Alec Kienzle on 8/18/21.
//

#include <iostream>
#include <string>
using namespace std;

const int ROWS = 5;
const int COLS = 5;

class Minesweeper
{
private:
    int row;
    int col;
    
public:
    void makeBoard(char board[][COLS])
    {
        for (int i = 0; i < COLS; i++)
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
        for (int i = 0; i <= COLS; i++)
        {
            cout << i << " ";
        }
    
        cout << endl;
    
        for (int i = 0; i < COLS; i++)
        {
            cout << i+1 << " ";
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
        row = i;
        col = j;
        
        if (board[row][col] == '*')
            cout << "You died!" << endl;
        else
            cout << "You're still alive." << endl;
    }
    
    void updateBoard(char realBoard[][COLS], char gameBoard[][COLS])
    {
        if (realBoard[row][col] == '*')
            gameBoard[row][col] = '*';
        else
            gameBoard[row][col] = 'S';
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
    game.move(realBoard);
    cout.setf(ios::boolalpha);
    cout << game.isAlive(realBoard) << endl;
    game.updateBoard(realBoard, gameBoard);
    game.printBoard(gameBoard);
    
    return(0);
}
