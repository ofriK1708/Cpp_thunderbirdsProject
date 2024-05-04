#include "board.h"
#include "gameConfig.h"
#include "utils.h"


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
		ships[i].init(GameConfig::SHIPS_SYMBOLS[i], GameConfig::SHIPS_CARRY_WEIGHT[i], GameConfig::SHIPS_COLORS[colorShift][i], this);

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
            switch (board[i][j]) {
                case 'T':
                    time.setLocation(j, i);
                    break;
                case GameConfig::HEALTH_SYMBOL:
                    health = { j, i };
                    break;
				case '#':
                    ships[0].addPoint(j, i);
                    break;
                case '@':
                    ships[1].addPoint(j, i);
                    break;
                case 'X':
                    exit_pos.set(j, i);
                    break;
				case 'B':
					ships[0].addFinishPoint(j, i);
					break;
				case 'S':
					ships[1].addFinishPoint(j, i);
					break;
                default:
                    if (board[i][j] >= '0' && board[i][j] <= '9') 
					{
                        size_t block_index = board[i][j] - '0';
                        if (!blocks[block_index].getSymbol()) {
                            blocks[block_index].init(board[i][j], GameConfig::BLOCK_COLOR, this);
                        }
                        blocks[block_index].addPoint(j, i);
                    }
                    break;
            }
		}
	}
}


bool Board::checkMove(LocationInfo &ol)
{
	int currY, currX;
	char currSymbol;
	bool isValid = true,isfinished = false;
	vector <Block*> obsticals;
	for(int i=0; i<ol.objSize && isValid; i++)
	{
		currY = ol.nextPos[i].getY();
		currX = ol.nextPos[i].getX();

		currSymbol = board[currY][currX];
		if (currSymbol != ' ' && currSymbol != ol.objSymbol)
			if (currSymbol == 'W')
				isValid = false;
			else if(currSymbol == 'X' && (ol.objSymbol == '#' || ol.objSymbol == '@'))
			{
				isfinished = true;
			}
			else if(currSymbol >= '0' && currSymbol<= '9'){ 
				addObstacle(obsticals, currSymbol, { currX, currY }); 
			}
			else {
				isValid = false; //if collide with other ship
			}
	}

	for (int i = 0; i < obsticals.size() && isValid; i++) {
		if (!(obsticals.at(i)->move(ol.direction, ol.carryWeight)))
			isValid = false;
	}
	if(isfinished && isValid)
	{
		shipFinishLine(ol.objSymbol);
		isValid = false; // there is no reason to move after we finished 
	}
	return isValid;
}


void Board::shipFinishLine(char shipID)
{
	switch (shipID)
	{
	case '#':
		ships[0].shipFinishLine();
		break;
	case '@':
		ships[1].shipFinishLine();
		break;
	}
}

void Board::addObstacle(vector <Block*> &obs, char currSymbol, Coord coord) {
	//check if it is a new obsticle or not
	bool newObstacle = true;
	Block *currBlock;
	currBlock = &blocks[board[coord.y][coord.x] - '0'];
	for (int i = 0; i < obs.size() && newObstacle; i++) {

		if (currBlock == obs.at(i))
			newObstacle = false;
	}
	if (newObstacle)
		obs.push_back(currBlock);
}
