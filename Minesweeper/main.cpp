//
//  main.cpp
//  Minesweeper
//
//  Created by Alec Kienzle on 8/18/21.
//

#include <iostream>
#include "Minesweeper.h"
#include "Board.h"

int main() {
    
    Board b;
    b.setRowAndColSize(5, 5);
    b.makeBoard();
    b.printBoard();

    /*
    Minesweeper game;
    game.cheatGame();
    game.playGame();
    */
    return(0);
}
