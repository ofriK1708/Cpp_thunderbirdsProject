#pragma once
#include <string>
#include "gameConfig.h"
#include <fstream>
using std::string;
using std::ifstream;

class Mapsfiles
{
	char legend[3][GameConfig::GAME_WIDTH + 1] = {
		"T                                                         WWWW            W    W",
		"W                                                         WBBW           WSW   W",
		"W L                                                       WBBW           WSW   W"
	};
	int userChoice = 0;
	string fileName;
	bool fileStatus = false;
	ifstream fileMap;
	void checkFileStatus();
	void searchMapFile();
	void copyHeaderToMap(char map[][GameConfig::GAME_WIDTH + 1],int line);

	
public:
	void GetUserFileChoice();
	void getMap(char map[][GameConfig::GAME_WIDTH + 1]);
	
	
};

