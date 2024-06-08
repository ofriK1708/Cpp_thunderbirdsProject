#pragma once

#include "point.h"
#include "ship.h"
#include "block.h"
#include "gameConfig.h"
#include "time.h"
#include "health.h"
#include "utils.h"
#include "mapsfiles.h"

#include <iostream>
#include <cstring>
#include <vector>


class Board {
	constexpr static size_t WIDTH = GameConfig::GAME_WIDTH;
	constexpr static size_t HEIGHT = GameConfig::GAME_HEIGHT;
	size_t num_blocks = 0;
	// the original board that will be copied to the actual board
	/*
	char original_board[HEIGHT][WIDTH + 1] = {
		//   01234567890123456789012345678901234567890123456789012345678901234567890123456789
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 0
			"W T                                                       WWWW            W    W", // 1
			"W                                                         WBBW           WSW   W", // 2
			"W L                                                       WBBW           WSW   W", // 3
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 4
			"WWWWWWWWWWWWWWW        33  WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW                   W", // 5
			"W@@          11  W     3                                                       W", // 7
			"WWWWWWWWWWWWWWW  WWWWWW0WWWWWWWWWWWWWWWWWWWWWWWW   55555        22  X          W", // 8
			"W             WWWWWWW  4                       W  WWWWWWWWWWWWWWWW  WWWWWWWWWWWW", // 9
			"W                   W  444                     W  W              WWWWWWWWWWWWWWW", // 10
			"W                   WWWWWWW                    W  WWW            WWWWWWWWWWWWWWW", // 11
			"W          W   W          W                    W   W                           W", // 12
			"W            W            W                    W   W                           W", // 13
			"W        W       W        W   WWWWWWWWWWWWWWWWWW   WWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 14
			"W         WWWWWWW         W   W                                                W", // 15
			"W                         W   W                                                W", // 16
			"WWWWWWWWWWWWWWWWWWWWWWWWWWW   W                                                W", // 17
			"                              W                                                 ", // 6
			"                              W                                                 ", // 18
			"W   WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW", // 19
			"W   W                                                                          W", // 20
			"W   W                                                                          W", // 21
			"W## W                                                                          W", // 22
			"W## W                                                                          W", // 23
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"  // 24
	};
	*/
	bool mapFileLoaded = false;
	char original_board[HEIGHT][WIDTH + 1];
	Time time;
	Health health;
	Point life_pos;
	Point exit_pos;	
	Ship ships[GameConfig::NUM_SHIPS];
	Block blocks[GameConfig::MAX_NUM_BLOCKS];
	Mapsfiles maps;
	bool colorSet = false;

	void addObstacle(vector <Block*>& obs, char currSymbol, Coord coord);

public:
	void loadMapFiles();
	char board[HEIGHT][WIDTH + 1];  // the actual board that will be modified
	void init(bool colorSet, bool mapChoose);
	void printScreen();
	void updateGamePieces();
	bool checkMove(LocationInfo& objectLoction);
	Ship* getShips() {return ships;}
	Block* getBlocks() { return blocks; }
	Time& getTime() { return time; }
	Health& getHealth() { return health; }
	void shipFinishLine(char shipID);
	bool getMapFileStatus() const { return mapFileLoaded; }
};