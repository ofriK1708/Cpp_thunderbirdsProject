#include <iostream>
#include "game.h"
#include "gameConfig.h"

using namespace std;

void startGame();

int main()
{
    startGame();
    return 0;
}

void startGame()
{
    Game theGame;
    bool pressedExit = theGame.mainMenu();
    if (!pressedExit) 
    {
        theGame.init();
        theGame.gameLoop();
    }
}
