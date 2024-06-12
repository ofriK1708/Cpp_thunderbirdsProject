#pragma once
#include "game.h";

class StateManager
{
	Game game;
	bool mapChoose = false;
	bool colorSet = true;
	bool toExit = false;
	
	void pauseMenu();
	bool mainMenu();

};

