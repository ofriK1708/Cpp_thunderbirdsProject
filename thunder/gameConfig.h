#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H

#include <Windows.h>


class GameConfig
{
public:
	enum class eKeys { LEFT = 'a', RIGHT = 's', UP = 'w', DOWN = 'z', ESC = 27 };
	static constexpr int GAME_WIDTH = 20;
	static constexpr int GAME_HEIGHT = 20;

	static constexpr int MIN_X = 10;
	static constexpr int MIN_Y = 3;

	static const int COLORS[];
	static const int NUM_OF_COLORS;
};
#endif