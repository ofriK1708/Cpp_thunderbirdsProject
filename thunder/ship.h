#ifndef SNAKE_H
#define SNAKE_H

#include "point.h"

struct ObjPos {
	const Point* pos = nullptr;
	size_t len = 0;
	char symbol = ' ';
};

class Ship
{
private:
	constexpr static size_t MAX_SHIP_SIZE = 4;
	Point pos[MAX_SHIP_SIZE];
	Point nextPos[MAX_SHIP_SIZE];
	char symbol;
	size_t size = 0;
	int backgroundcolor;
	char (*board)[81]; // pointer to the board
public:
	void init(char symbol, int color, char(*board)[81]);
	void move();
	void addPoint(int x, int y) { pos[size++].set(x, y);}
	size_t getSize() const			{return size;}
	Point getPos(size_t i) const	{return pos[i];}
	void delTrace();
	ObjPos getNextPos(GameConfig::eKeys direction);
	//bool checkCollision(int x, int y); // placed here for a lack of better option, would move in the future
};

#endif
