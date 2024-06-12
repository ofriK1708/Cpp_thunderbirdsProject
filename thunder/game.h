#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include  <stdbool.h>
#include <map>

#include "ship.h"
#include "board.h"
#include "utils.h"
#include "time.h"
#include "gameConfig.h"
#include "stepsIO.h"
#include "StepInput.h"
#include "KeyboardInput.h"

using namespace std;

class Ship;

enum class GameState {
	RUNNING = 0, //The game shall run 
	PAUSE, //puase the game
	WIN, //the game is finished and the player won
	LOSE //the game is finished and the player lost
};


class Game
{
	Board board;
	Point timelocation;
	size_t level = 1;
	KeyboardInput ki;
	StepInput* userInput = &ki;

	//game pieces
	Health health;
	Time time;
	Ship* ships;
	map <char, Block>* blocks;

	//configurations
	int gameTime = GameConfig::GAME_TIME;
	int gameSpeed = GameConfig::MIN_SLEEP; // for sleep function
	
	//data global indicators
	int activeShip = 0; // 0 - Big Ship, 1 - Small Ship	
	bool freezeSips = false;
	int keyPressed;
	bool mapfileLoaded;
	GameState gameState;
	bool timeOver = false;
	bool colorSet = true;
	bool mapChoose = false;

	void setKey(int key) { keyPressed = tolower(key); }
	void ShipAction();
	void play();
	void resetBoard();
	void afterDeath();
	void gameFinish();

public:
	void prepareToStart();
	void gameLoop();
	bool getMapFileStatus() const { return mapfileLoaded; }
	void printScreen() { board.printScreen(); }
	void printCredits();
};

#endif