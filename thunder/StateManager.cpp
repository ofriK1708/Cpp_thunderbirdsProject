#include "StateManager.h"

#include <conio.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::to_string;
using std::exception;


StateManager::StateManager(int argc, char* argv[]){
	switch (argc) {
	case 1:
		mode = Mode::SIMPLE;
		break;
	case 2:
		if (argv[1] == "-load") {
			mode = Mode::LOAD_FROM_FILE;
		}else if (argv[1] == "-save") {
				mode = Mode::SAVE_TO_FILE;
		}else{
			exceptionHandler(exception("Game Mode not avaliable"));
		}
		break;
	case 3:
		mode = Mode::SILENT_LOAD_FROM_FILE;
		if (argv[1] == "-load" and argv[2] == "-silent") {
			mode = Mode::SILENT_LOAD_FROM_FILE;
		}
		else if (argv[1] == "-save" and argv[2] == "-silent") {
			mode = Mode::SAVE_TO_FILE;
		}
		else {
			exceptionHandler(exception("Game Mode not avaliable"));
		}
		break;
	default:
		exceptionHandler(exception("Game Mode not avaliable"));
	}
}


void StateManager::exceptionHandler(const exception& e) {
	toExit = true;
	clrscr();
	cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*- Game Paused *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*" << endl;
	cout << "Exception: " << e.what() << endl;
	cout << "Exiting game ...";
	Sleep(GameConfig::LONG_SLEEP);
}


void StateManager::startGame()
{
	if (!toExit) {
		mainMenu();
		if (!toExit)
		{
			try {
				game.prepareToStart();
				game.gameLoop();
			}
			catch (const exception& e) {
				exceptionHandler(e);
			}
		}
	}
}


void StateManager::mainMenu()
{
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
			toExit = true;
			break;
		default:
			cout << "invalid choice, please try again" << endl;
			break;
		}
	} while (userChoice != 1 && !toExit);
	Sleep(GameConfig::SHORT_SLEEP);
	clrscr();
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

