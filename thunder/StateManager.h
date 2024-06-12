#pragma once
#include "game.h";

enum class Mode {
	SIMPLE = 0,
	SAVE_TO_FILE,
	LOAD_FROM_FILE,
	SILENT_LOAD_FROM_FILE
};

class StateManager
{
	Game game;
	Mode mode;
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

