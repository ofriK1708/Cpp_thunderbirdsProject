#include "ResultIO.h"
#include "GameSleep.h"


void ResultIO::writeEvent(int timeLeft, Events event) {
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

	wfp.getFile() << message << std::endl;
}


void ResultIO::setMode(FileMode _mode) {
	mode = _mode;
	loadFileByMode();
}

void ResultIO::loadFileByMode() {
	if (currLevel != level) {
		currLevel = level;
		timeStamp = GameConfig::GAME_TIME + 1;

		switch (mode) {
		case FileMode::write:
			rfp.close();
			wfp.close();
			GameSleep::systemOprSleep();
			wfp.open(getFileName());
			break;
		case FileMode::read:
			rfp.close();
			wfp.close();
			GameSleep::systemOprSleep();
			rfp.open(getFileName());
			break;
		default:
			throw std::exception("Chosen mode not exist");
			break;
		}
	}
}

