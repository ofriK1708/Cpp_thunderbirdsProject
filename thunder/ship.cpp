#include "ship.h"
#include "utils.h"
#include <cstring>


void Ship::init(char symbol, int color, char (*board)[81])
{
	this->symbol = symbol;
	this->backgroundcolor = color;
	this->board = board;
}


/**
 * Moves the ship in the specified direction.
 *
 * @param direction The direction in which to move the ship.
 */
void Ship::move()
{
	delTrace();
	std::memcpy(pos, nextPos, sizeof(pos));
	for (size_t i = 0; i<size; i++)
	{
		pos[i].draw(symbol, backgroundcolor);
		board[pos[i].getY()][pos[i].getX()] = symbol;
	}
	hideCursor();
}


ObjPos Ship::getNextPos(GameConfig::eKeys direction) {
	ObjPos op;

	std::memcpy(nextPos, pos, sizeof(pos));
	for (size_t i = 0; i < size; i++)
		nextPos[i].move(direction);
	op.pos = this->nextPos;
	op.len = this->size;
	op.symbol = this->symbol;
	return op;
}


/**
 * Deletes the trace of the ship.
 *
 * @param lastPos An array of Points representing the previous positions of the ship.
 */
void Ship::delTrace() {
	for (int i = 0; i < size; i++) {
		pos[i].draw(' ', GameConfig::BLACK);
		board[pos[i].getY()][pos[i].getX()] = ' ';
	}
}
