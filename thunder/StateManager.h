#pragma once
#include "game.h";

class StateManager
{
	Game game;
	bool mapChoose = false;
	bool colorSet = true;
	bool toExit = false;
	
	bool mainMenu();
	void pauseMenu();
	void exceptionHandler(const exception& e);

	
public:
	void startGame();
};

