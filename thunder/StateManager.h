#pragma once
#include "game.h"

class StateManager
{
	Game game;
	StepsIO stepsIO;
	KeyboardInput keyboardStepsInput;

	bool mapChoose = false;
	bool colorSet = true;
	static bool toExit;
	
	void mainMenu();
	void pauseMenu();
	
	void setMode(int argc, char* argv[]);


	
public:
	StateManager(int argc, char* argv[]);
	static void exceptionHandler(const exception& e);
	void startGame();
};

