#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "ship.h"
#include "board.h"
#include "utils.h"
#include "time.h"
#include "gameConfig.h"
#include  <stdbool.h>

using namespace std;

class Ship;

class Game
{
	Board board;
	bool colorSet = false; 
	Health health;
	Time time;
	int gameTime = GameConfig::GAME_TIME;
	bool timeOver = false;
	int gameSpeed = 30; // for sleep function, low values make the game run faster
	Ship* ships;
	Point timelocation;
	int activeShip = 0; // 0 - Big Ship, 1 - Small Ship
	bool running = false;
	bool stopGame = false;
	int keyPressed;
	int userChoice;
public:
	void init();
	void mainMenu();
	void setKey(int key) { keyPressed = tolower(key); }
	void setGameStatus();
	void gameLoop();
	void play();
	void pauseMenu();
	void resetBoard();
	void afterDeath();

};

#endif