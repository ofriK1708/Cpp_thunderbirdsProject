#include "StateManager.h"
#include "conio.h"


bool StateManager::mainMenu()
{
	bool isExit = false;
	unsigned short userChoice;
	cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* Thunderbirds: Escape from the Egyptian Tomb *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
	do {
		cout << "Please enter your choice" << endl;
		cout << "1: Start a new game" << endl;
		cout << "2: Set color ON/OFF (the default value is on)" << endl;
		cout << "3: load a specific map" << endl;
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
		case 3:
			cout << "No problem, when you will start a new game, you will choose the map :)" << endl;
			mapChoose = true;
			break;
		case 8:
			cout << endl;
			cout << "Objective :" << endl << "Escape the ancient Egyptian tomb by maneuvering the two trapped ships, a big ship(2x2) and a small ship(2x1), through obstacles and reaching the exit before time runs out" << endl << endl;
			cout << "Controls: " << endl << "Use WASD to move the active ship" << endl;
			cout << "W - Up" << endl << "A - Left" << endl << "S - Down" << endl << "D - Right" << endl;
			cout << "Press 'B' or 'S' to switch control between the big and small ships" << endl << "Press 'ESC' to pause the game." << endl << endl;
			break;
		case 9:
			clrscr();
			cout << "Exiting the game, please come back when you can :D";
			Sleep(GameConfig::SHORT_SLEEP);
			isExit = true;
			break;
		default:
			cout << "invalid choice, please try again" << endl;
			break;
		}
	} while (userChoice != 1 && !isExit);
	Sleep(GameConfig::SHORT_SLEEP);
	clrscr();
	return isExit;
}


void StateManager::pauseMenu() {

	bool illigalChoice = true;
	char userInput;

	cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*- Game Paused *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*" << endl;
	cout << "Press ESC again to continue or 9 to Exit" << endl;
	while (illigalChoice) {
		while (!_kbhit())
			Sleep(GameConfig::MIN_SLEEP);
		userInput = _getch();
		switch (userInput)
		{
		case (int)GameConfig::eKeys::ESC:
			clrscr();
			cout << "Returning to the game, get ready" << endl;;
			Sleep(GameConfig::SHORT_SLEEP);
			clrscr();
			game.printScreen();
			illigalChoice = false;
			break;
		case (int)GameConfig::eKeys::EXIT:
			clrscr();
			game.printCredits();
			toExit = true;
			illigalChoice = false;
			break;
		}
	}
}

