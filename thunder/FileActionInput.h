#pragma once
#include "StepInput.h"
#include "smartReadFile.h"
#include "gameConfig.h"

#include <fstream>
#include <string>

using std::string;
using std::string;


class FileActionInput : public StepInput
{	
	smartReadFile f;
	const size_t &currTime, &level;
	int timeStamp = GameConfig::GAME_TIME + 1, currAction = false;
	size_t currLevel = 0;

	const string stepsEnding = ".steps";
	const string prefix = "tb0";
	string fileName;
	
	void loadFile();

public:
	FileActionInput(const size_t &currTime, size_t &level) : currTime(currTime), level(level) {};
	virtual char getAction() const override { return currAction; }
	virtual bool hasInput() override;
};

