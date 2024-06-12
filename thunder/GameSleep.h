#pragma once
#include "gameConfig.h"

#include <Windows.h>


class GameSleep
{
	static constexpr size_t longOprTime = GameConfig::LONG_SLEEP;
	static constexpr size_t shortOprTime = GameConfig::SHORT_SLEEP;
	static constexpr size_t systemOprTime = GameConfig::SYSTEM_OPR_SLEEP;
	static constexpr size_t gameSpeed = GameConfig::GAME_SPEED;
	static constexpr size_t minTime = GameConfig::MIN_TIME;

public:
	static bool silentMode;
	static void sleep(size_t milliSec) {
		if (silentMode)
			Sleep(minTime);
		else
			Sleep(milliSec);
	}
	static void longSleep() { sleep(longOprTime); }
	static void shortSleep() { sleep(shortOprTime); }
	static void systemOprSleep() { sleep(systemOprTime); }
	static void gameOprSleep() { sleep(gameSpeed); }
};

