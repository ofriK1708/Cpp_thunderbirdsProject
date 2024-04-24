#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "ship.h"
#include "board.h"
#include "utils.h"
#include  <stdbool.h>

using namespace std;

class Ship;

class Game
{
	Board board;
	bool colorSet = false; 
	//activeShip
public:
	void init();
	void run();
	void mainMenu();
};

#endif