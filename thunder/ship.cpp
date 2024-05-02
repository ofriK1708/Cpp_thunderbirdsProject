#include "block.h"
#include "utils.h"
#include "board.h"


void Ship::init(char symbol, GameConfig::Color color, Board *board)
{
	this->symbol = symbol;
	this->backgroundcolor = color;
	this->board = board;
}


void Ship::move(GameConfig::eKeys direction)
{
	
		delTrace();
		std::copy(std::begin(nextPos), std::end(nextPos), std::begin(pos));
		Block* blocks = board->getBlocks();
		int currY, currX;
		char currSymbol;
		for (size_t i = 0; i < size; i++)
		{
			currY = pos[i].getY();
			currX = pos[i].getX();
			currSymbol = board->board[currY][currX];
			if ((currSymbol >= '0' && currSymbol <= '9'))
			{
				blocks[currSymbol - '0'].move(direction);
			}
			pos[i].draw(symbol, backgroundcolor);
			board->board[currY][currX] = symbol;
		}
		hideCursor();
}


LocationInfo& Ship::checkNextObjLocation(GameConfig::eKeys direction) {
	std::copy(std::begin(pos), std::end(pos), std::begin(nextPos));
	for (size_t i = 0; i < size; i++)
		nextPos[i].move(direction);
	shipLocationinfo = { nextPos, symbol, size };
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
