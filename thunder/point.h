#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <Windows.h>

#include "gameConfig.h"
#include "utils.h"

using namespace std;


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

#endif