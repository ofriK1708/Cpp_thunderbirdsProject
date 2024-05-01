#include "ship.h"
#include "utils.h"
#include <cstring>
#include "board.h"


void Block::init(char symbol, GameConfig::Color color, Board* board)
{
	this->symbol = symbol;
	this->backgroundcolor = color;
	this->board = board;
}


void Block::move(GameConfig::eKeys direction)
{
	if (!(board->checkCollision(checkNextObjLocation(direction)))) {
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
	}
}


LocationInfo& Block::checkNextObjLocation(GameConfig::eKeys direction) {
	std::copy(std::begin(pos), std::end(pos), std::begin(nextPos));
	for (size_t i = 0; i < size; i++)
		nextPos[i].move(direction);
	locationInfo = { nextPos, symbol, size };
	return locationInfo;
}


void Block::delTrace() {
	int currY, currX;
	for (int i = 0; i < size; i++)
	{
		currY = pos[i].getY();
		currX = pos[i].getX();
		pos[i].draw(' ', GameConfig::BLACK);
		board->board[currY][currX] = ' ';
	}
}
