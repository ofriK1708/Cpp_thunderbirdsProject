#include "board.h"
#include "gameConfig.h"
#include "Color.h"
void Board::init(bool colorSet){

	int smallShipColor = WHITE;
	int bigShipColor = WHITE;
	if(colorSet)
	{
		smallShipColor = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		bigShipColor = BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;
	}
    ships[0].init(GameConfig::SHIPS_SYMBOLS[0], bigShipColor); // setting big ship
	ships[1].init(GameConfig::SHIPS_SYMBOLS[1], smallShipColor); // setting small ship
	updateGamePieces();
	printScreen();
}

void Board::printScreen() {
	for (size_t j = 0; j < GameConfig::MIN_Y; j++)
		std::cout << endl;
	for (int i = 0; i < HEIGHT; i++) {
		for (size_t j = 0; j < GameConfig::MIN_X; j++)
			std::cout << " ";
		std::cout << board[i] << std::endl;
	}
}

void Board::updateGamePieces(){
	std::memcpy(board, original_board, sizeof(original_board));
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (board[i][j] == '&') {
				legend_pos.set(j, i);
			}
			else if (board[i][j] == GameConfig::SHIPS_SYMBOLS[0]) {
				ships[0].addPoint(j, i);
			}
			else if (board[i][j] == GameConfig::SHIPS_SYMBOLS[1]) {
				ships[1].addPoint(j, i);
			}
			else if (board[i][j] >= '0' && board[i][j] <= '9') {
				size_t block_index = board[i][j] - '0';
				blocks[block_index].addPoint(j, i);
			}
			else if (board[i][j] == 'X') {
				exit_pos.set(j, i);
			}
		}
	}
}