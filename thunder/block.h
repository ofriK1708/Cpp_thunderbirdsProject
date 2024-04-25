#pragma once

#include "point.h"

class Board;


class Block {
	constexpr static size_t MAX_BlOCK_SIZE = 6;
	Point pos[MAX_BlOCK_SIZE];
	char symbol;
	size_t size = 0;
	Board* board = nullptr; // pointer to the board
	int backgroundcolor;
public:
	void setBoard(Board* board)		{this->board = board;}
	void addPoint(int x, int y)		{pos[size++].set(x, y);}
	size_t getSize() const			{return size;}
	Point getPos(size_t i) const	{return pos[i];}
	void move(GameConfig::eKeys direction);
	//bool checkCollision(int x, int y); // placed here for a lack of better option, would move in the future
};