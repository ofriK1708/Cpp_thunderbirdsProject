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
	
	delTrace();
	int currY, currX;
	Block* blocks = board->getBlocks();
	std::copy(std::begin(nextPos), std::end(nextPos), std::begin(pos));
	char currSymbol;
	for (size_t i = 0; i < size; i++)
	{
			currY = pos[i].getY();
			currX = pos[i].getX();
			currSymbol = board->board[currY][currX];
			if ((currSymbol != this->symbol) && (currSymbol >= '0' && currSymbol <= '9'))
			{
				blocks[currSymbol - '0'].move(direction);
			}
			board->board[currY][currX] = ' ';
			pos[i].draw(symbol, backgroundcolor);
			board->board[currY][currX] = symbol;
	}
	hideCursor();
	
	
}

void Block::fallDown() 
{
	if ((board->checkCollision(checkNextObjLocation(GameConfig::eKeys::DOWN),GameConfig::eKeys::DOWN)))
	{
		move(GameConfig::eKeys::DOWN);
	}
}


LocationInfo& Block::checkNextObjLocation(GameConfig::eKeys direction) 
{
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
