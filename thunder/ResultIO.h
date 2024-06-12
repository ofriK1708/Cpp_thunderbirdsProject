#pragma once

#include "SmartFile.h"
#include "smartReadFile.h"
#include "SmartWriteFile.h"
#include "gameConfig.h"

#include <string>


using std::string;

enum class FileMode { read = 0, write };
enum class Events {
	DEATH,
	FINISH_LEVEL
};
class ResultIO{

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
	ResultIO(const size_t& currTime, const size_t& level) :currTime(currTime), level(level) { loadFileByMode(); currLevel = 0; }
	void setMode(FileMode _mode);
	void writeEvent(int timeLeft, Events event);
};

void Result::writeEvent(int timeLeft, Events event) {
	string message;

	switch (event) {
	case Events::DEATH:
		message = "death";
		break;
	case Events::FINISH_LEVEL:
		message = "finish";
		break;
	default:
		message = "unknown";
		break;
	}
	message.append(" ");
	message.append(std::to_string(timeLeft));

	write(message);
}
