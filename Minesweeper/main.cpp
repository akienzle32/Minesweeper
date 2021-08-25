//
//  main.cpp
//  Minesweeper
//
//  Created by Alec Kienzle on 8/18/21.
//

#include <iostream>
#include "Minesweeper.h"

int main() {

    Minesweeper game;
    game.placeMines();
    game.cheatGame();
    
    return(0);
}
