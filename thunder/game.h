#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include  <stdbool.h>

#include "ship.h"
#include "board.h"
#include "utils.h"
#include "time.h"
#include "gameConfig.h"

using namespace std;

class Ship;

class Game
{
		
	Board board;
	Point timelocation;

	//game pieces
	Health health;
	Time time;
	Ship* ships;
	Block* blocks;
	
	//configurations
	int gameTime = GameConfig::GAME_TIME;
	int gameSpeed = GameConfig::MIN_SLEEP; // for sleep function
	
	//data globals
	int activeShip = 0; // 0 - Big Ship, 1 - Small Ship	
	int keyPressed;
	int userChoice;
	
	//indicator globas
	bool timeOver = false;
	bool running = false;
	bool stopGame = false;
	bool colorSet = false;

	void setKey(int key) { keyPressed = tolower(key); }
	void setGameStatus();
	void play();
	void pauseMenu();
	void resetBoard();
	void afterDeath();
	void gameFinish();
	void printCredits();

public:
	void init();
	bool mainMenu();
	void gameLoop();
};

#endif