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
    for (int i = 0; i < COLS; i++)
    {
        
    }
    
    
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}


int main() {

    
    char gameBoard[ROWS][COLS];
    char realBoard[ROWS][COLS];
    
    makeBoard(gameBoard);
    printBoard(gameBoard);
    makeBoard(realBoard);
    placeMines(realBoard);
    
    return(0);
}
