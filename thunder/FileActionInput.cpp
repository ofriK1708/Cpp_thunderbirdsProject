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
	if (cmdInterrupt()) {
		currAction = (char)GameConfig::eKeys::ESC;
		return true;
	}
	if (timeStamp == currTime)
		return true;
	if (timeStamp > currTime) {
		string line;
		getline(f.getFile(), line);
		std::sscanf(line.c_str(), "%d %d", &timeStamp, &currAction);
	}
	return false;
}
