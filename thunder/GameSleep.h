#pragma once
#include "gameConfig.h"

#include <Windows.h>


class GameSleep
{
	bool silentMode = false;
	static constexpr size_t longOprTime = GameConfig::LONG_SLEEP;
	static constexpr size_t shortOprTime = GameConfig::SHORT_SLEEP;
	static constexpr size_t systemOprTime = GameConfig::SYSTEM_OPR_SLEEP;

public:
	void sleep(size_t milliSec) {
		if (silentMode)
			Sleep(systemOprTime);
		else
			Sleep(milliSec);
	}
	void longSleep() { sleep(longOprTime); }
	void shortSleep() { sleep(shortOprTime); }
	void systemOprSleep() { sleep(systemOprTime); }
};

