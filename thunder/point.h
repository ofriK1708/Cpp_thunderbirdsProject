#pragma once

#include "gameConfig.h"

class Point
{
	int x;
	int y;
	int diff_x;
	int diff_y;

public:
	void init(int x, int y);
	void draw(char ch, int backcolor);
	void move(GameConfig::eKeys key);
};

