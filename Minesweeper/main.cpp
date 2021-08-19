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
    void makeBoard(char array[][COLS])
    {
        for (int i = 0; i < COLS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                array[i][j] = '-';
            }
        }
    }

    void placeMines(char array[][COLS])
    {
        array[0][3] = '*';
        array[2][1] = '*';
        array[3][2] = '*';
        array[4][3] = '*';
    }

    void printBoard(char array[][COLS])
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
                cout << array[i][j] << " ";
            }
            cout << endl;
            }
    }

    bool isAlive(char array[][COLS])
    {
        bool result = true;
        if (array[row][col] == '*')
            result = false;
        return(result);
    }

    void move(char array[][COLS])
    {
        int i, j;
        cout << "Pick a spot on the board (row, column):\n";
        cin >> i; cin >> j;
        row = i;
        col = j;
        
        if (array[row][col] == '*')
            cout << "You died!" << endl;
        else
            cout << "You're still alive." << endl;
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
    
    return(0);
}
