#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H

#include <Windows.h>


class GameConfig
{
public:
	enum class eKeys { LEFT = 'a', RIGHT = 'd', UP = 'w', DOWN = 'x', SWITCH_TO_SMALL_S = 's', SWITCH_TO_BIG_S = 'b', ESC = 27, EXIT = (int)'9' };
	static constexpr int GAME_WIDTH = 80;
	static constexpr int GAME_HEIGHT = 25;

	static constexpr int MIN_X = 10;
	static constexpr int MIN_Y = 3;

	static constexpr size_t GAME_TIME = 400;
	static constexpr size_t LIVES = 3;
	static constexpr char HEALTH_SYMBOL = 'L';


	enum Color
	{
		BLACK = 0,
		BLUE = 1,
		GREEN = 2,
		CYAN = 3,
		RED = 4,
		MAGENTA = 5,
		BROWN = 6,
		LIGHTGREY = 7,
		DARKGREY = 8,
		LIGHTBLUE = 9,
		LIGHTGREEN = 10,
		LIGHTCYAN = 11,
		LIGHTRED = 12,
		LIGHTMAGENTA = 13,
		YELLOW = 14,
		WHITE = 15, 
		PURPLE = BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY,
		TURQUOISE = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY

	};


	static const size_t NUM_SHIPS = 2;
	static const char SHIPS_SYMBOLS[NUM_SHIPS];
	static const Color SHIPS_COLORS[NUM_SHIPS][NUM_SHIPS];
	enum ShipID {
		BIG = 0,
		SMALL = 1
	};
	
};
#endif