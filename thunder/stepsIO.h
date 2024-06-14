#pragma once

#include "SmartFile.h"
#include "smartReadFile.h"
#include "SmartWriteFile.h"
#include "StepInput.h"
#include "gameConfig.h"

#include <string>


using std::string;


class StepsIO: public StepInput{
public:
	enum class FileMode { read = 0, write };
private: 
	FileMode mode = FileMode::read;
	smartReadFile rfp;
	SmartWriteFile wfp;
	const string stepsEnding = ".steps.txt", prefix = "tb0";
	const size_t& currTime, & level;
	size_t timeStamp = GameConfig::GAME_TIME + 1, currAction = false;
	size_t currLevel = 0;
	bool is_silent = false;
	void loadFileByMode();
	string getFileName() const {return prefix + std::to_string(level) + stepsEnding; }
public:
	StepsIO(const size_t& currTime, const size_t& level) :currTime(currTime), level(level) { loadFileByMode(); currLevel = 0; }
	void setMode(FileMode _mode);
	virtual char getAction() const override {return currAction; }
	virtual bool hasInput() override;
	void writeStep(size_t step, size_t timeLeft);
	void setSilent(bool silent) { is_silent = silent; }
};
