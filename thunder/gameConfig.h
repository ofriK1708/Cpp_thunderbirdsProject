#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

class GameConfig
{
public:
	enum class eKeys { LEFT = 'a', RIGHT = 'd', UP = 'w', DOWN = 's', ESC = 27 };
	static constexpr int GAME_WIDTH = 20;
	static constexpr int GAME_HEIGHT = 20;

	static constexpr int MIN_X = 10;
	static constexpr int MIN_Y = 3;
};
#endif
