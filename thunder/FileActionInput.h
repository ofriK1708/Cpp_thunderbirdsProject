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
	const int &timeStamp, &level;
	bool gotInput = false;
	int currTime = GameConfig::GAME_TIME + 1, currAction;

	const string stepsEnding = ".steps";
	const string prefix = "tb0";
	string fileName;
	
	void loadFile() { f.open(prefix + std::to_string(level) + stepsEnding); }

public:
	FileActionInput(const int &timeStamp, size_t &level) : timeStamp(timeStamp), level(level) {};
	virtual char getAction() const override { return currAction; }
	virtual bool hasInput() override;

	//~FileActionInput();
};

