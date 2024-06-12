#include "StateManager.h"
#include "GameSleep.h"

#include <conio.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::to_string;
using std::exception;



StateManager::StateManager(int argc, char* argv[]): stepsIO(game.getTimeLeft(), game.getLevel()){
	setMode(argc, argv);
}

void StateManager::setMode(int argc, char* argv[]) {
	string errorMessage = "Game Mode not avaliable: ";
	switch (argc) {
	case 1:
		game.setMode(GameMode::SIMPLE, &keyboardStepsInput, nullptr);
		break;
	case 2:
		if (!strcmp(argv[1],"-load")) {
			game.setMode(GameMode::LOAD_FROM_FILE, &stepsIO, nullptr);
		}
		else if (!strcmp(argv[1],"-save")) {
			game.setMode(GameMode::SAVE_TO_FILE, &keyboardStepsInput, &stepsIO);
		}
		else {
			errorMessage.append(argv[1]);
			exceptionHandler(exception(errorMessage.c_str()));
		}
		break;
	case 3:
		if (!strcmp(argv[1], "-load") and !strcmp(argv[2], "-silent")) {
			game.setMode(GameMode::SILENT_LOAD_FROM_FILE, &stepsIO, nullptr);
			GameSleep::silentMode = true;
		}
		else if (!strcmp(argv[1], "-save") and !strcmp(argv[2], "-silent")) {
			game.setMode(GameMode::SAVE_TO_FILE, &keyboardStepsInput ,&stepsIO);
		}
		else {
			errorMessage.append(argv[1]);
			errorMessage.append(" ");
			errorMessage.append(argv[2]);
			exceptionHandler(exception(errorMessage.c_str()));
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
	GameSleep::longSleep();
}


void StateManager::startGame()
{
	if (!toExit) {
		mainMenu();
		if (!toExit)
		{
			try {
				game.prepareToStart();
				while (game.getState()!=GameState::WIN and game.getState()!= GameState::LOSE and !toExit) {
					game.gameLoop();
					if (game.getState() == GameState::PAUSE) {
						pauseMenu();
						if (!toExit)
							game.setStateToRunning();
					}
				}
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
			GameSleep::shortSleep();
			toExit = true;
			break;
		default:
			cout << "invalid choice, please try again" << endl;
			break;
		}
	} while (userChoice != 1 && !toExit);
	GameSleep::shortSleep();
	clrscr();
}


void StateManager::pauseMenu() {

	bool illigalChoice = true;
	char userInput;

	cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*- Game Paused *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*" << endl;
	cout << "Press ESC again to continue or 9 to Exit" << endl;
	while (illigalChoice) {
		while (!_kbhit())
			GameSleep::systemOprSleep();
		userInput = _getch();
		switch (userInput)
		{
		case (int)GameConfig::eKeys::ESC:
			clrscr();
			cout << "Returning to the game, get ready" << endl;;
			GameSleep::shortSleep();
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

