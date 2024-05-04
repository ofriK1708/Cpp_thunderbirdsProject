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
	int maxCarryWeight;
	GameConfig::Color backgroundcolor;
	LocationInfo shipLocationinfo;

	size_t getSize() const { return size; }
	Point getPos(size_t i) const { return pos[i]; }
	char getSymbol() { return symbol; }
	void delTrace();
	LocationInfo& checkNextObjLocation(GameConfig::eKeys direction, int* carryWeight);

public:
	void init(char symbol, int maxCarryWeight, GameConfig::Color color, Board* Board);
	GameConfig::Color getBackgroundColor() { return backgroundcolor; }
	void addPoint(int x, int y) { pos[size++].set(x, y); }
	bool move(GameConfig::eKeys direction);
	GameConfig::gamePieceType getType() { return type; }
};

#endif
