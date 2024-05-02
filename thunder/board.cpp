#include "board.h"
#include "gameConfig.h"
#include "utils.h"
#include "vector"


/**
 * Initializes the game board and its components.
 *
 * This function initializes the game board and its components, including ships, blocks,
 * the exit, and the legend position. It then updates the game pieces on the board and
 * prints the initial state of the game screen.
 */

void Board::init(bool colorSet)
{
	this->colorSet = colorSet;
	size_t colorShift = 0;
	if (colorSet)
		colorShift++;

	for (size_t i = 0; i < GameConfig::NUM_SHIPS; i++)
		ships[i].init(GameConfig::SHIPS_SYMBOLS[i], GameConfig::SHIPS_COLORS[colorShift][i], this);

	updateGamePieces();
	printScreen();
}

int isShip(char ch) {
	int res = -1;
	
	for (int i = 0; i < GameConfig::NUM_SHIPS; i++)
		if (GameConfig::SHIPS_SYMBOLS[i] == ch)
			res = i;
	return res;
}


/**
 * Prints the current state of the game board on the screen with appropriate indentation.
 */
void Board::printScreen() {
	for (size_t j = 0; j < GameConfig::MIN_Y; j++)
		std::cout << endl;
	for (int i = 0; i < HEIGHT; i++) {
		for (size_t j = 0; j < GameConfig::MIN_X; j++)
			std::cout << " ";
		for (size_t j = 0; j < WIDTH; j++){
			int shipIndex = isShip(board[i][j]);
			if (shipIndex != -1) {
				setTextColor(ships[shipIndex].getBackgroundColor());
				std::cout << board[i][j];
				setTextColor(GameConfig::WHITE);
			}
			else if(board[i][j] == 'W' && colorSet)
			{
				setTextColor(GameConfig::BACKGROUND_GREY);
				std::cout << board[i][j];
				setTextColor(GameConfig::WHITE); 
			}
			else	
				std::cout << board[i][j];
		}
		std::cout << endl;
	}
}

/**
 * Updates the game pieces on the board based on the current state.
 *
 * This function updates the positions of various game pieces such as ships, blocks, exit,
 * and legend position on the board according to the current state of the game.
 */
void Board::updateGamePieces()
{
	std::memcpy(board, original_board, sizeof(original_board));
	for (int i = 0; i < HEIGHT; i++) 
	{
		for (int j = 0; j < WIDTH; j++) 
		{
			if (board[i][j] == 'T') 
				time.setLocation( j, i );
			if (board[i][j] == GameConfig::HEALTH_SYMBOL)
				health = { j, i };
			else if (board[i][j] == GameConfig::SHIPS_SYMBOLS[0]) 
				ships[0].addPoint(j, i);
			else if (board[i][j] == GameConfig::SHIPS_SYMBOLS[1]) 
				ships[1].addPoint(j, i);
			else if (board[i][j] >= '0' && board[i][j] <= '9') 
			{
				size_t block_index = board[i][j] - '0';
				if (!blocks[block_index].getSymbol()) // if the bloack hasnt initialized yet
					blocks[block_index].init(board[i][j], GameConfig::BLOCK_COLOR, this);
				blocks[block_index].addPoint(j, i);
			}
			else if (board[i][j] == 'X') 
				exit_pos.set(j, i);
		}
	}
}

bool Board::checkCollision(LocationInfo &ol,GameConfig::eKeys direction)
{
	int totalSize = 0;
	return (checkCollisionHelper(ol, &totalSize, direction));
}


bool Board::checkCollisionHelper(LocationInfo &ol,int * totalSize,GameConfig::eKeys direction)
{
	
	int currX,currY;
	LocationInfo * nextOL = nullptr;
	for(int i=0; i<ol.objSize; i++)
	{
		currY = ol.nextPos[i].getY();
		currX = ol.nextPos[i].getX();
		if (board[currY][currX] != ' ' && board[currY][currX] != ol.objSymbol)
		{
			if (board[currY][currX] == 'W')
			{
				return false;
			}
			else if (board[currY][currX] >= '0' && board[currY][currX] <= '9')
			{
				if (nextOL == nullptr)
					nextOL = &blocks[board[currY][currX] - '0'].checkNextObjLocation(direction);
			}
			else // another ship
			{
				return false;
			}
		}
	}
	if (nextOL != nullptr)
	{
		*totalSize += nextOL->objSize;
		if (checkCollisionHelper(*nextOL, totalSize,direction) && checkWightLimit(*totalSize, ol.objSymbol))
		{
	
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

bool checkWightLimit(int totalSize,char objId)
{
	if (objId == GameConfig::SHIPS_SYMBOLS[0])
	{
		if(totalSize > GameConfig::SHIP_MAX_WEIGHT[0])
			return false;

	}
	else if (objId == GameConfig::SHIPS_SYMBOLS[1])
	{
		if(totalSize > GameConfig::SHIP_MAX_WEIGHT[1])
			return false;
	}
	else // a block
	{
		return true; // block doesn't care about weight
	}
	return true; // the weight is valid for the ship
}


bool Board::moveable(Coord coord, char symbol) {
	if (board[coord.y][coord.x] != symbol)
		return false;
	return true;
}

bool Board::isGamePiece(char pieceSymbol) {
	for (int i = 0; i < GameConfig::MAX_NUM_BLOCKS; i++) {
		if (pieceSymbol == GameConfig::BLOCK_SYMBOLS[i])
			return true;
	}
	for (int i = 0; i < GameConfig::NUM_SHIPS; i++) {
		if (pieceSymbol == GameConfig::SHIPS_SYMBOLS[i])
			return true;
	}
	return false;
}
