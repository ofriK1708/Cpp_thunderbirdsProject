#ifndef BLOCK_H
#define BLOCK_H

#include "point.h"
#include "utils.h"

class Board;

class Block
{
private:
	Board* board;
	Point pos[GameConfig::MAX_BLOCK_SIZE];
	Point nextPos[GameConfig::MAX_BLOCK_SIZE];
	char symbol = NULL;
	GameConfig::gamePieceType type = GameConfig::SECONDARY;
	size_t size = 0;
	GameConfig::Color backgroundcolor;
	LocationInfo locationInfo;
	size_t getSize() const { return size; }
	Point getPos(size_t i) const { return pos[i]; }
	void delTrace();
	

public:
	LocationInfo& checkNextObjLocation(GameConfig::eKeys direction);
	void fallDown();
	void init(char symbol, GameConfig::Color color, Board* Board);
	GameConfig::Color getBackgroundColor() { return backgroundcolor; }
	void addPoint(int x, int y) { pos[size++].set(x, y); }
	void move(GameConfig::eKeys direction = GameConfig::eKeys::DOWN);
	GameConfig::gamePieceType getType() { return type; }
	char getSymbol() { return symbol; }
	size_t getSize() { return size; }
};

#endif
