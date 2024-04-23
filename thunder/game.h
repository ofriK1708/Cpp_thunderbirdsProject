#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H


#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>

#include "snake.h"
#include "utils.h"
#include  <stdbool.h>

using namespace std;

class Snake;

class Game
{
	Snake* allSnakes;
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