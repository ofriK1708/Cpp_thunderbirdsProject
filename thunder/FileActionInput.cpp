#define _CRT_SECURE_NO_WARNINGS

#include "FileActionInput.h"
#include "gameConfig.h"

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>


bool cmdInterrupt() {
	bool interrupt = false;
	if (_kbhit())
		if ((GameConfig::eKeys)_getch() == GameConfig::eKeys::ESC)
			interrupt = true;
	return interrupt;
}

bool FileActionInput::hasInput(){
	loadFile();
	if (cmdInterrupt()) {
		currAction = (char)GameConfig::eKeys::ESC;
		return true;
	}
	if (timeStamp == currTime)
		return true;
	if (timeStamp > currTime) {
		string line;
		getline(f.getFile(), line);
		std::sscanf(line.c_str(), "%d %d", &currAction, &timeStamp);
	}
	return false;
}

void FileActionInput::loadFile() {
	if (currLevel != level) {
		currLevel = level;
		timeStamp = GameConfig::GAME_TIME + 1;
		f.open(prefix + std::to_string(level) + stepsEnding);
	}
}