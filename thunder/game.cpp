#include "game.h"
#include "steps.h"
#include "mapsfiles.h"

#include <stdlib.h>
#include <iostream>
//#include <conio.h>
#include <Windows.h>


void Game::init()
{
	resetBoard();
	if (mapfileLoaded) {
		health = board.getHealth();
	}
	stepsFile.openFile(1);
}

void Game::resetBoard()
{
	board = Board();// board.reset(); or write operator= in the mapfiles class
	board.init(colorSet,mapChoose);
	if (board.getMapFileStatus()) 
	{
		mapfileLoaded = true;
		ships = board.getShips();
		blocks = board.getBlocks();
		time = board.getTime();
		time.setTimeSettings(gameTime, colorSet);
	}
	else
	{
		mapfileLoaded = false;
	}
}

void clear() {
	gotoxy(0, 0);
	clrscr();
}

//Manages the main menu interface and user interaction.
bool Game::mainMenu()  
{
	bool isExit = false;
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
			clear();
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

void Game::pauseMenu() {
	
	bool illigalChoice = true;
	
	cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*- Game Paused *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*" << endl;
	cout << "Press ESC again to continue or 9 to Exit" << endl;
	while (illigalChoice) {
		while (!_kbhit())
			Sleep(GameConfig::MIN_SLEEP);
		setKey(_getch());
		switch (keyPressed)
		{
		case (int)GameConfig::eKeys::ESC:
			clear();
			cout << "Returning to the game, get ready" << endl;;
			Sleep(GameConfig::SHORT_SLEEP);
			clear();
			board.printScreen();
			illigalChoice = false;
			break;
		case (int)GameConfig::eKeys::EXIT:
			clear();
			printCredits();
			stopGame = true;
			illigalChoice = false;
			break;
		}
	}
}

void Game::gameFinish()
{
	clear();
	cout << "*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*  YOU WON!!!!!  *-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
	printCredits();

}

void Game::printCredits()
{
	cout << "Finished game, Thank you for playing :D" << endl;;
	cout << "*-*-*-*-*-*-*-* Ofri & Or *-*-*-*-*-*-*-*" << endl << endl;
}

void Game::setGameStatus() 
{
	if(ships[0].GetFinishStatus() && ships[1].GetFinishStatus()) // if the player sussecfuly finished the level 
	{
		stopGame = true;
		gameFinish();
	}
	else
	{
		switch (keyPressed)
		{
		case (int)GameConfig::eKeys::ESC:
			clear();
			pauseMenu();
			keyPressed = 0;
			running = false;
			break;

		case (int)GameConfig::eKeys::SWITCH_TO_BIG_S:
			if (activeShip == GameConfig::ShipID::SMALL)
				activeShip = GameConfig::ShipID::BIG;
			else
				running = false;
			break;

		case (int)GameConfig::eKeys::SWITCH_TO_SMALL_S:
			if (activeShip == GameConfig::ShipID::BIG)
				activeShip = GameConfig::ShipID::SMALL;
			else
				running = false;
			break;

		case (int)GameConfig::eKeys::UP:
		case (int)GameConfig::eKeys::DOWN:
		case (int)GameConfig::eKeys::LEFT:
		case (int)GameConfig::eKeys::RIGHT:
			running = true;
			break;
		};
	}
}

void Game::play() {
	if(running)
		ships[activeShip].move((GameConfig::eKeys)keyPressed);
	for(auto & pair: *blocks)
		pair.second.move();
}


void Game::afterDeath() 
{
	if (health.getlivesLeft() > 1) // if we are at 1 and died then game over 
	{
		 clear();
		 cout << "!-!-!-!-!-!-!-! Sorry for that, try again :) !-!-!-!-!-!-!-!" << endl;
		 health.decreaseLife();
		 this->timeOver = false;
		 Sleep(GameConfig::LONG_SLEEP);
		 clear();
	
		 resetBoard();
		 health.printHealth();
		 running = false;
		 keyPressed = 0;
	}
	else
	{
		clear();
		cout << "!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-! GAME OVER !-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!" << endl;
		printCredits();
		stopGame = true;
	}
}


/**
 * Runs the game loop, handling player input.
 */
void Game::gameLoop()
{
	keyPressed = 0;

	while (!stopGame && !timeOver && health.isAlive())
	{
		if (_kbhit()) { //get rid from this and put in the cmd class
			lt = { time.getTimeLeft(), 1 };
			setKey(userInput->getAction(&lt));
			stepsFile.writeStep(keyPressed, time.getTimeLeft());
		}
		setGameStatus();
		if (!stopGame) 
		{
			play();
			timeOver = time.checkAndupdateTime();
			health.printHealth();
		}
		Sleep(gameSpeed);
		if (timeOver)
			afterDeath();
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::WHITE);
}