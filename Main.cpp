/**
Main.cpp
Particle simulator Author: Henry Bryant

*/
#include "Game.h"
#include <fstream>
#include <string.h>
#include <iostream>

int main()
{
    Game game;
    //game loop

    while (game.isRunning())
    {
        //update 
        game.update();

        //render
       game.render();
    }
    //end of application
    return 0;
}