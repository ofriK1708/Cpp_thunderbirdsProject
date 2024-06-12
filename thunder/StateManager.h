#pragma once
#include "game.h"

class StateManager
{
	Game game;
	StepsIO stepsIO;
	KeyboardInput keyboardStepsInput;

	bool mapChoose = false;
	bool colorSet = true;
	bool toExit = false;
	
	void mainMenu();
	void pauseMenu();
	void exceptionHandler(const exception& e);
	void setMode(int argc, char* argv[]);


	
public:
	StateManager(int argc, char* argv[]);
	void startGame();
};

