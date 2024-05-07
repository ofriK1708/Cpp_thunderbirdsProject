#pragma once

#include "gameConfig.h"
#include "utils.h"

class Health
{
	int x;
	int y;
	size_t livesLeft = GameConfig::LIVES;
	char healthSymbol = GameConfig::HEALTH_SYMBOL;
	bool isColor = false;

public:
	void setLocation(int x, int y) { this->x = x; this->y = y; }
	void decreaseLife() { --livesLeft; }
	size_t getlivesLeft() { return livesLeft; }
	bool isAlive();
	void printHealth();
	void setColor(bool isColor) { this->isColor = isColor; }
};

