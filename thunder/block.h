#ifndef BLOCK_H
#define BLOCK_H

#include "point.h"


class Board;

class Block
{
private:
	Board* board;
	Point pos[GameConfig::MAX_SHIP_SIZE];
	Point nextPos[GameConfig::MAX_SHIP_SIZE];
	char symbol;
	size_t size = 0;
	GameConfig::Color backgroundcolor;
	LocationInfo shipLocationinfo;

	size_t getSize() const { return size; }
	Point getPos(size_t i) const { return pos[i]; }
	char getSymbol() { return symbol; }
	void delTrace();
	LocationInfo& checkNextObjLocation(GameConfig::eKeys direction);

public:
	void init(char symbol, GameConfig::Color color, Board* Board);
	GameConfig::Color getBackgroundColor() { return backgroundcolor; }
	void addPoint(int x, int y) { pos[size++].set(x, y); }
	void move(GameConfig::eKeys direction);

};

#endif
