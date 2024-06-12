#pragma once

#include "SmartFile.h"
#include "smartReadFile.h"
#include "SmartWriteFile.h"
#include "StepInput.h"
#include "gameConfig.h"

#include <string>


using std::string;

enum class Mode { read = 0, write };

class StepsIO: public StepInput{
	
private: 
	Mode mode;
	smartReadFile rfp;
	SmartWriteFile wfp;
	const string stepsEnding = ".steps", prefix = "tb0";
	const size_t& currTime, & level;
	size_t timeStamp = GameConfig::GAME_TIME + 1, currAction = false;
	size_t currLevel = 0;
	
	void loadFileByMode();
	string getFileName() const {return prefix + std::to_string(level) + stepsEnding; }

public:
	StepsIO(Mode mode, const size_t& currTime, size_t& level);
	virtual char getAction() const override { return currAction; }
	virtual bool hasInput() override;
	void writeStep(size_t step, size_t timeLeft);

};
