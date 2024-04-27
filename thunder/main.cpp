#include <iostream>

#include "test.h"
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

    theGame.mainMenu();
    theGame.init();
    theGame.run();
}
