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


bool Board::checkCollision(LocationInfo &ol)
{
	int currY, currX;
	bool newObsticle;
	vector <Coord> coords;
	for(int i=0; i<ol.objSize; i++)
	{
		currY = ol.nextPos[i].getY();
		currX = ol.nextPos[i].getX();
		if (board[currY][currX] != ' ' && board[currY][currX] != ol.objSymbol)
			if (!moveable({ currX, currY }, ol.objSymbol))
				return true;
			else {
				newObsticle = true;
				for (int i = 0; i < coords.size() && newObsticle; i++) {
					if (board[coords.at(i).y][coords.at(i).x] == board[currY][currX])
						false;
				}
				if (newObsticle)
					coords.push_back({ currX, currY });
			}
	}
	return false;
}

bool Board::moveable(Coord coord, char symbol) {
	if (board[coord.y][coord.x] != symbol)
		return false;
	return true;
}
