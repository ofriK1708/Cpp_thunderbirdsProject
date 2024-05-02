#include "block.h"
#include "utils.h"
#include "board.h"


void Ship::init(char symbol, GameConfig::Color color, Board *board)
{
	this->symbol = symbol;
	this->backgroundcolor = color;
	this->board = board;
}


bool Ship::move(GameConfig::eKeys direction)
{
	if (board->checkMove(checkNextObjLocation(direction))) {
		delTrace();
		std::copy(std::begin(nextPos), std::end(nextPos), std::begin(pos));
		int currY, currX;
		for (size_t i = 0; i < size; i++)
		{
			currY = pos[i].getY();
			currX = pos[i].getX();
			pos[i].draw(symbol, backgroundcolor);
			board->board[currY][currX] = symbol;
		}
		hideCursor();
		return true;
	}
	return false;
}


LocationInfo& Ship::checkNextObjLocation(GameConfig::eKeys direction) {
	std::copy(std::begin(pos), std::end(pos), std::begin(nextPos));
	for (size_t i = 0; i < size; i++)
		nextPos[i].move(direction);
	shipLocationinfo = { nextPos, symbol, size , direction};
	return shipLocationinfo;
}


void Ship::delTrace() {
	int currY, currX;
	for (int i = 0; i < size; i++) 
	{
		currY = pos[i].getY();
		currX = pos[i].getX();
		pos[i].draw(' ', GameConfig::BLACK);
		board->board[currY][currX] = ' ';
	}
}
