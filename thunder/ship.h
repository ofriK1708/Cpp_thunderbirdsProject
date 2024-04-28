#ifndef SNAKE_H
#define SNAKE_H

#include "point.h"


struct LocationInfo {
	Point* nextPos = nullptr;
	char objSymbol = ' ';
	size_t objSize = 0;
};


class Ship
{
private:
	constexpr static size_t MAX_SHIP_SIZE = 4;
	Point pos[MAX_SHIP_SIZE];
	Point nextPos[MAX_SHIP_SIZE];
	char symbol;
	size_t size = 0;
	GameConfig::Color backgroundcolor;
	char (*board)[81]; // pointer to the board
	LocationInfo shipLocationinfo;
public:
	void init(char symbol, GameConfig::Color color, char(*board)[81]);
	void move();
	void addPoint(int x, int y) { pos[size++].set(x, y);}
	size_t getSize() const			{return size;}
	Point getPos(size_t i) const	{return pos[i];}
	char getSymbol() { return symbol; }
	void delTrace();
	LocationInfo& checkNextObjLocation(GameConfig::eKeys direction);
	GameConfig::Color getBackgroundColor() { return backgroundcolor;}

};

#endif
