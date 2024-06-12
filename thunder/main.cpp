#include <iostream>

#include "StateManager.h"
#include "gameConfig.h"
#include "GameSleep.h"

using namespace std;
bool GameSleep::silentMode = false;


int main(int argc, char* argv[])
{
    StateManager stateManager(argc, argv);
    stateManager.startGame();
    return 0;
}

