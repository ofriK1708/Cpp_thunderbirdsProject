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
	int currY,currX;
	for (size_t i = 0; i<size; i++)
	{
		currY = pos[i].getY();
		currX = pos[i].getX();
		pos[i].draw(symbol, backgroundcolor);
		board[currY][currX] = symbol;
	}
	hideCursor();
}


void Ship::setNextPos(GameConfig::eKeys direction) {

	std::memcpy(nextPos, pos, sizeof(pos));
	for (size_t i = 0; i < size; i++)
		nextPos[i].move(direction);
}


/**
 * Deletes the trace of the ship.
 *
 * @param lastPos An array of Points representing the previous positions of the ship.
 */
void Ship::delTrace() {
	int currY, currX;
	for (int i = 0; i < size; i++) 
	{
		currY = pos[i].getY();
		currX = pos[i].getX();
		pos[i].draw(' ', GameConfig::BLACK);
		board[currY][currX] = ' ';
	}
}
