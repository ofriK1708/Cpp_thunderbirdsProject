#pragma once

#include "SmartFile.h"
#include "smartReadFile.h"
#include "SmartWriteFile.h"
#include "gameConfig.h"

#include <string>


using std::string;

enum class Events {
	DEATH,
	FINISH_LEVEL
};
class ResultIO{
public:
	enum class FileMode { read = 0, write };
private:
	FileMode mode = FileMode::read;
	smartReadFile rfp;
	SmartWriteFile wfp;
	const string stepsEnding = ".result.txt", prefix = "tb0";
	const size_t& currTime, & level;
	size_t timeStamp = GameConfig::GAME_TIME + 1, currAction = false;
	size_t currLevel = 0;

	void loadFileByMode();
	string getFileName() const { return prefix + std::to_string(level) + stepsEnding; }

public:
	ResultIO(const size_t& currTime, const size_t& level) :currTime(currTime), level(level) {currLevel = 0; }
	void setMode(FileMode _mode);
	void writeEvent(int timeLeft, Events event);
};
