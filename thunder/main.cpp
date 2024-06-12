#include <iostream>

#include "StateManager.h"
#include "gameConfig.h"

using namespace std;


int main(int argc, char* argv[])
{
    StateManager stateManager(argc, argv);

    stateManager.startGame();
    return 0;
}

