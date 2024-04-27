#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "ship.h"
#include "board.h"
#include "utils.h"
#include  <stdbool.h>

#define NUM_OF_SHIPS 2

using namespace std;

class Ship;

class Game
{
	Board board;
	bool colorSet = false; 
	Ship ships[NUM_OF_SHIPS];
	int activeShip = 0; // 0 - Big Ship, 1 - Small Ship
public:
	void init();
	void run();
	void mainMenu();
};

#endif