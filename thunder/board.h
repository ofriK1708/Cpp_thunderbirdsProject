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
#include <map>


class Board {
	constexpr static size_t WIDTH = GameConfig::GAME_WIDTH;
	constexpr static size_t HEIGHT = GameConfig::GAME_HEIGHT;
	size_t num_blocks = 0;
	bool mapFileLoaded = false;
	char original_board[HEIGHT][WIDTH + 1];
	Time time;
	Health health;
	Point life_pos;
	Point exit_pos;	
	Ship ships[GameConfig::NUM_SHIPS];
	map<char, Block> blocks;
	Mapsfiles maps;
	bool colorSet = false;
	size_t levels;

public:
	void loadMapFiles();
	char board[HEIGHT][WIDTH + 1];  // the actual board that will be modified
	void init(bool colorSet, bool mapChoose);
	void printScreen();
	void updateGamePieces();
	bool checkMove(LocationInfo& objectLoction);
	Ship* getShips() {return ships;}
	map <char, Block> * getBlocks() { return &blocks; }
	Time& getTime() { return time; }
	Health& getHealth() { return health; }
	void shipFinishLine(char shipID);
	bool getMapFileStatus() const { return mapFileLoaded; }
	size_t getNumOfLevels() const { return levels; }
	void loadNextMap() { maps.loadNextMap();}
};