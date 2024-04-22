#pragma once
#include <iostream>
#include <Windows.h>

#include "gameConfig.h"
#include "utils.h"

using namespace std;


class Point
{
	int x;
	int y;
	int diff_x = 0;
	int diff_y = 0;

public:
	Point(int x, int y) { this->x = x; this->y = y; }
	void draw(char ch, int backcolor);
	void move(GameConfig::eKeys key);
};