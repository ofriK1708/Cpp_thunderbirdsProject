#include "board.h"
#include "gameConfig.h"


/**
 * Initializes the game board and its components.
 *
 * This function initializes the game board and its components, including ships, blocks,
 * the exit, and the legend position. It then updates the game pieces on the board and
 * prints the initial state of the game screen.
 */
void Board::init(){

	for (size_t i=0; i<NUM_SHIPS; i++) 
		ships[i].init(GameConfig::SHIPS_SYMBOLS[i], GameConfig::COLORS[i+1]);
	updateGamePieces();
	printScreen();
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
		std::cout << board[i] << std::endl;
	}
}


/**
 * Updates the game pieces on the board based on the current state.
 *
 * This function updates the positions of various game pieces such as ships, blocks, exit,
 * and legend position on the board according to the current state of the game.
 */
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
