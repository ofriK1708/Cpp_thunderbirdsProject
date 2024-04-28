#include <iostream>

#include "test.h"
#include "game.h"
#include "gameConfig.h"

using namespace std;

void startGame();

int main()
{
    startGame();
    gotoxy(0, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 1);
    return 0;
}

void startGame()
{
    Game theGame;

    theGame.mainMenu();
    theGame.init();
    theGame.gameLoop();
}
