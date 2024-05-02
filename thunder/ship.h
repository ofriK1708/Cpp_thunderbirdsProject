#ifndef SHIP_H
#define SHIP_H

#include "point.h"
#include "utils.h"


class Board;

class Ship
{
private:
	Board* board;
	Point pos[GameConfig::MAX_SHIP_SIZE];
	Point nextPos[GameConfig::MAX_SHIP_SIZE];
	char symbol;
	GameConfig::gamePieceType type = GameConfig::PRIMARY;
	size_t size = 0;
	GameConfig::Color backgroundcolor;
	LocationInfo shipLocationinfo;

	
	Point getPos(size_t i) const { return pos[i]; }
	char getSymbol() { return symbol; }
	void delTrace();
	

public:
	size_t getSize() const { return size; }
	LocationInfo& checkNextObjLocation(GameConfig::eKeys direction);
	void init(char symbol, GameConfig::Color color, Board* Board);
	GameConfig::Color getBackgroundColor() { return backgroundcolor; }
	void addPoint(int x, int y) { pos[size++].set(x, y); }
	void move(GameConfig::eKeys direction);
	GameConfig::gamePieceType getType() { return type; }
};

#endif
