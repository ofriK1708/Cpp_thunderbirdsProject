#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H


#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>

#include "ship.h"
#include "utils.h"
#include  <stdbool.h>

using namespace std;

class Ship;

class Game
{
	Ship* allSnakes;
	int numOfSnakes;
	bool colorSet = false; 
	void drawBorder();
public:
	void init(int num);
	void run();
	void freeMemory();
	void mainMenu();
};

#endif