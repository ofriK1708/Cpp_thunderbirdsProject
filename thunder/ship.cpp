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
void Ship::move(GameConfig::eKeys direction)
{
	Point lastPos[MAX_SHIP_SIZE];
	std::memcpy(lastPos, pos, sizeof(pos));
	for (size_t i = 0; i<size; i++)
	{
		pos[i].move(direction);
		pos[i].draw(symbol, backgroundcolor);
		board[pos[i].getX()][pos[i].getY()] = symbol;
	}
	delTrace(lastPos);
	hideCursor();
}


/**
 * Deletes the trace of the ship.
 *
 * @param lastPos An array of Points representing the previous positions of the ship.
 */
void Ship::delTrace(Point lastPos[]) {
	bool toDel;
	for (int i = 0; i < size; i++) {
		toDel = true;
		for (int j = 0; j < size; j++) {
			if ((lastPos[i] == pos[j]))
				toDel = false;
		}
		if (toDel) {
			lastPos[i].draw(' ', GameConfig::BLACK);
			board[pos[i].getX()][pos[i].getY()] = ' ';
		}
	}
}
