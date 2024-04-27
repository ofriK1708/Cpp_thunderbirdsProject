#ifndef POINT_H
#define POINT_H

#include "gameConfig.h"

using namespace std;


class Point
{
	int x = -1, y = -1;
	int diff_x = 0;
	int diff_y = 0;

public:
	void set(int x, int y);
	void draw(char symbol, int backcolor);
	void move(GameConfig::eKeys key);
	void getCoordinate(int& x, int& y) {x = this->x; y = this->y;}
	int getX() const { return this->x; }
	int getY() const { return this->y; }
	bool operator==(const Point& other) const {
		if ((this->x == other.x) && (this->y == other.y))
			return true;
		else
			return false;
	}
};

#endif