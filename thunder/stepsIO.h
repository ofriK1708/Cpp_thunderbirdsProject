#pragma once

#include "SmartFile.h"
#include "smartReadFile.h"
#include "SmartWriteFile.h"
#include "StepInput.h"

#include <string>


using std::string;

//= dynamic_cast<smartReadFile*>(SmartFile);
class StepsIO: public StepInput{
	enum class Mode{read=0, write};
	Mode mode;
	SmartFile& file;
	smartReadFile* rfp = nullptr;
	SmartWriteFile* rfp = nullptr;
	const string stepsEnding = ".steps", prefix = "tb0";
	const size_t& currTime, & level;
	size_t timeStamp = GameConfig::GAME_TIME + 1, currAction = false;
	size_t currLevel = 0;
	
	void loadFile();

public:
	StepsIO(Mode mode, const size_t& currTime, size_t& level) : mode(mode), currTime(currTime), level(level);
	virtual char getAction() const override { return currAction; }
	virtual bool hasInput() override;
	void writeStep(size_t step, size_t timeLeft);

};
