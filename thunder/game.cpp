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

void Game::mainMenu()  
{
	int userChoice;
	cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Thunderbirds: Escape from the Egyptian Tomb *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
	do {
		cout << "Please enter your choice" << endl;
		cout << "1: Start a new game" << endl;
		cout << "2: Set color ON/OFF (the default value is off)" << endl;
		cout << "8: Instructions and keys" << endl;
		cout << "9: Exit" << endl;
		cin >> userChoice;
		switch (userChoice)
		{
		case 1:
			cout << "Great, setting up the game, have fun!! :D";
			break;
		case 2:
			colorSet = !colorSet;
			colorSet ? cout << "color is now set on" : cout << "color is now set off";
			cout << endl;
			break;
		case 8:
			cout << endl;
			cout << "Objective :" << endl << "Escape the ancient Egyptian tomb by maneuvering the two trapped ships, a big ship(2x2) and a small ship(2x1), through obstacles and reaching the exit before time runs out" << endl << endl;
			cout << "Controls: " << endl << "Use WASD to move the active ship" << endl;
			cout << "W - Up" << endl << "A - Left" << endl << "S - Down" << endl << "D - Right" << endl;
			cout << "Press 'B' or 'S' to switch control between the big and small ships" << endl << "Press 'ESC' to pause the game." << endl << endl;
			break;
		case 9:
			cout << "exiting the game";
			exit(0); // Not sure about that 
		default:
			cout << "invalid choice, please try again" << endl;
			break;
		}
	} while (userChoice != 1);
	Sleep(700);
	clrscr();
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

