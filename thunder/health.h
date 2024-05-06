#pragma once

#include "gameConfig.h"
#include "utils.h"

class Health
{
	size_t x;
	size_t y;
	size_t livesLeft = GameConfig::LIVES;
	char healthSymbol = GameConfig::HEALTH_SYMBOL;
	bool isColor = false;

public:
	void setLocation(int x, int y) { this->x = x; this->y = y; }
	void decreaseLife() { --livesLeft; }
	bool isAlive();
	void printHealth();
	void setColor(bool isColor) { this->isColor = isColor; }
};

