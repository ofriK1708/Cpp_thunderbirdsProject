#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "ship.h"
#include "board.h"
#include "utils.h"
#include "gameConfig.h"
#include  <stdbool.h>

using namespace std;

class Ship;

class Game
{
	Board board;
	bool colorSet = false; 
	Ship ships[GameConfig::NUM_SHIPS];
	int activeShip = 1; // 0 - Big Ship, 1 - Small Ship
public:
	void init();
	void run();
	void mainMenu();
};

#endif