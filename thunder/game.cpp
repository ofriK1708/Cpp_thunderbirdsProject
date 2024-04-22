#include "game.h"

void Game::init(int num)
{
	drawBorder();

	numOfSnakes = num;
	allSnakes = new Snake[numOfSnakes];
	for (int i = 0; i < numOfSnakes; i++)
	{
		Point head;
		head.init(rand() % GameConfig::GAME_WIDTH, rand() % GameConfig::GAME_HEIGHT);
		allSnakes[i].init(head, '#', GameConfig::COLORS[(i % (GameConfig::NUM_OF_COLORS - 1)) + 1]);
	}
}
void Game::freeMemory()
{
	delete[]allSnakes;
}

void Game::drawBorder()
{
	for (int col = GameConfig::MIN_X; col < GameConfig::GAME_WIDTH + GameConfig::MIN_X; col++)
	{
		gotoxy(col, GameConfig::MIN_Y - 1);
		cout << "-";

		gotoxy(col, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y);
		cout << "-";
	}

	for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::GAME_HEIGHT + GameConfig::MIN_Y; row++)
	{
		gotoxy(GameConfig::MIN_X - 1, row);
		cout << "|";

		gotoxy(GameConfig::GAME_WIDTH + GameConfig::MIN_X, row);
		cout << "|";
	}
}

void Game::run()
{
	while (true)
	{
		int keyPressed = 0;
		if (_kbhit())
		{
			keyPressed = _getch();
			if (keyPressed == (int)GameConfig::eKeys::ESC)
			{
				gotoxy(0, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 1);
				break;
			}
		}
		Sleep(100);
		for (int i = 0; i < numOfSnakes; i++)
			allSnakes[i].move((GameConfig::eKeys)keyPressed);
	}
}

