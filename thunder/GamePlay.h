#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "gameConfig.h"


using std::ofstream;
using std::string;


class GamePlay
{
protected:
	const string prefix = "tb0";
	string ending;
	ofstream file;
	GameConfig::ErrorCode closeCurrFile();
	void write(string data);

public:
	~GamePlay();
	GameConfig::ErrorCode openFile(size_t level);
};

