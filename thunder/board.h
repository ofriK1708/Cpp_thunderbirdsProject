#pragma once

#include "point.h"
#include "ship.h"
#include "block.h"

#include <iostream>
#include <cstring>

class Board {
	constexpr static size_t WIDTH = 80;
	constexpr static size_t HEIGHT = 25;
	constexpr static size_t NUM_SHIPS = 2;
	constexpr static size_t NUM_BLOCKS = 1;
	// the original board that will be copied to the actual board
	char original_board[HEIGHT][WIDTH + 1] = {
		//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
			"W                                                                              W", // 1
			"W        &                                                                     W", // 2
			"W                                                                              W", // 3
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 4
			"W         @@                                                                   W", // 5
			"W         ##                                                                   W", // 6
			"W         ##                                                                   W", // 7
			"W                                                                              W", // 8
			"W                                                                              W", // 9
			"W                                                                              W", // 10
			"W                                                                              W", // 11
			"W                                                                              W", // 12
			"W                                                 WWWWWWWWWWWW                 W", // 13
			"W                                                                              W", // 14
			"W                                                 W         WWWW               W", // 15
			"W                                             WWWWW            W               W", // 16
			"W                                              00              W               W", // 17
			"W                                       W      00            X W               W", // 18
			"W                                       WWWWWWWWWWWWWWWWWWWWWWWW               W", // 19
			"W                                                                              W", // 20
			"W                                                                              W", // 21
			"W                                                                              W", // 22
			"W                                                                              W", // 23
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  // 24
	};
	// the actual board that will be modified
	char board[HEIGHT][WIDTH + 1];
	Ship ships[NUM_SHIPS];
	Block blocks[NUM_BLOCKS];
	Point legend_pos;
	Point exit_pos;
public:
	void init() {
		std::memcpy(board, original_board, sizeof(original_board));
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (board[i][j] == '&') {
					legend_pos.set(j, i);
				}
				else if (board[i][j] == '@') {
					ships[0].addPoint(j, i);
				}
				else if (board[i][j] == '#') {
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
	void show() {
		for (int i = 0; i < HEIGHT; i++) {
			std::cout << board[i] << std::endl;
		}
	}
};


