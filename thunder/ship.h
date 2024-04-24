#ifndef SNAKE_H
#define SNAKE_H

#include "point.h"

class Board;

class Ship
{
private:
	constexpr static size_t MAX_SHIP_SIZE = 4;
	Point pos[MAX_SHIP_SIZE];
	char symbol;
	size_t size = 0;
	int backgroundcolor;
	Board* board = nullptr; // pointer to the board
public:
	void init(char symbol, int color);
	void move(GameConfig::eKeys direction);
	void setBoard(Board* board)		{this->board = board;}
	void addPoint(int x, int y) { pos[size++].set(x, y);}
	size_t getSize() const			{return size;}
	Point getPos(size_t i) const	{return pos[i];}
	void delTrace(Point lastPos[]);
	//bool checkCollision(int x, int y); // placed here for a lack of better option, would move in the future
};

#endif
