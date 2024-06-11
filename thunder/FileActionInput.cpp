#define _CRT_SECURE_NO_WARNINGS

#include "FileActionInput.h"
#include "gameConfig.h"

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>


bool cmdInterrupt() {
	if (_kbhit())
		if ((GameConfig::eKeys)_getch() == GameConfig::eKeys::ESC)
			return true;
	else
		return false; 
}

bool FileActionInput::hasInput(){
	if (cmdInterrupt()) {
		currAction = (char)GameConfig::eKeys::ESC;
		return true;
	}
	if (currTime == timeStamp)
		return true;
	if (currTime > timeStamp) {
		string line;
		getline(f.getFile(), line);
		std::sscanf(line.c_str(), "%d %d", &currTime, &currAction);
	}
	return false;
}
