#include "board.h"
#include "gameConfig.h"
#include "utils.h"

bool isBlock(char ch);

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

bool isBlock(char ch) 
{
	if(ch >= '0' && ch <= '9')
	{
		return true;
	}
	return false;
}
bool isShip(char ch)
{
	if(ch == GameConfig::BIG_SHIP_S || ch == GameConfig::SMALL_SHIP_S)
	{
		return true;
	}
	return false;
}


/**
 * Prints the current state of the game board on the screen with appropriate indentation.
 */
void Board::printScreen()
{
	GameConfig::Color color = GameConfig::WHITE;
	for (size_t j = 0; j < GameConfig::MIN_Y; j++)
		std::cout << endl;
	for (int i = 0; i < HEIGHT; i++) {
		for (size_t j = 0; j < GameConfig::MIN_X; j++)
			std::cout << " ";
		for (size_t j = 0; j < WIDTH; j++)
		{
			char currSymbol = board[i][j];
			if (colorSet)
			{
				switch (currSymbol)
				{
				case GameConfig::BIG_SHIP_S:
					color = ships[GameConfig::BIG_SHIP_ID].getBackgroundColor();
					break;
				case GameConfig::SMALL_SHIP_S:
					color = ships[GameConfig::SMALL_SHIP_ID].getBackgroundColor();
					break;
				case 'W':
					color = GameConfig::WALL_COLOR;
					break;
				case GameConfig::FINISH_S:
					color = GameConfig::WHITE_BACKGROUND;
					break;
				case 'L':
					health.setColor(colorSet);
				default:
					if (isBlock(currSymbol))
					{
						color = blocks[0].getBackgroundColor();
					}
					break;

				}

			}
			setTextColor(color);
			if(currSymbol == GameConfig::FINISH_BIG_SHIP || currSymbol == GameConfig::FINISH_SMALL_SHIP)
			{
				std::cout << ' ';
			}
			else
			{
				std::cout << currSymbol;
			}
			 
			setTextColor(color = GameConfig::WHITE);

		}
		std::cout << std::endl;
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
	GameConfig::Color blockColor = colorSet ? GameConfig::BLOCK_COLOR : GameConfig::WHITE;
	for (int i = 0; i < HEIGHT; i++) 
	{
		for (int j = 0; j < WIDTH; j++) 
		{
			char currSymbol = board[i][j];
            switch (currSymbol) 
			{
			    case GameConfig::TIME_SYMBOL:
                    time.setLocation(j, i);
                    break;
                case GameConfig::HEALTH_SYMBOL:
                    health.setLocation(j, i);
                    break;
				case GameConfig::BIG_SHIP_S:
                    ships[0].addPoint(j, i);
                    break;
                case GameConfig::SMALL_SHIP_S:
                    ships[1].addPoint(j, i);
                    break;
					case GameConfig::FINISH_S:
                    exit_pos.set(j, i);
                    break;
				case GameConfig::FINISH_BIG_SHIP:
					ships[0].addFinishPoint(j, i);
					break;
				case GameConfig::FINISH_SMALL_SHIP:
					ships[1].addFinishPoint(j, i);
					break;
                default:
                    if (isBlock(currSymbol))
					{
                        size_t block_index = currSymbol - '0';
                        if (!blocks[block_index].getSymbol()) 
						{
                            blocks[block_index].init(currSymbol, blockColor, this);
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
			else if(currSymbol == GameConfig::FINISH_S && isShip(ol.objSymbol))
			{
				isfinished = true;
			}
			else if(isBlock(currSymbol)){ 
				addObstacle(obsticals, currSymbol, { currX, currY }); 
			}
			else {
				isValid = false; //if collide with other ship
			}
	}

	for (int i = 0; i < obsticals.size() && isValid; i++) {
		if (!(obsticals.at(i)->checkMove(ol.direction, ol.carryWeight)))
			isValid = false;
	}
	if(isValid)
	{
		if (isfinished) {
			shipFinishLine(ol.objSymbol);
			isValid = false; // there is no reason to move after we finished 
		}
		else {
			for (int i = 0; i < obsticals.size() && isValid; i++) {
				obsticals.at(i)->move(ol.direction, ol.carryWeight, true);
			}
		}
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
