#include "game.h"

#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>

void Game::init()
{
	resetBoard();
	health.setLocation(board.getHealthLocation());
	health.setColor(colorSet);
	health.printHealth();
}

void Game::resetBoard()
{
	this->board = Board(); 
	board.init(colorSet);
	ships = board.getShips();
	blocks = board.getBlocks();
	time = board.getTime();
	time.setTimeSettings(gameTime, colorSet);
}

void clear() {
	gotoxy(0, 0);
	clrscr();
}

/**
* Manages the main menu interface and user interaction.
*/
void Game::mainMenu()  
{
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

void Game::pauseMenu() {
	
	cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*- Game Paused *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-**-*-*-*-*-*-*" << endl;
	cout << "Press ESC again to continue or 9 to Exit" << endl;
	while (!_kbhit())
		Sleep(100);
	setKey(_getch());
	switch (keyPressed)
	{
	case (int)GameConfig::eKeys::ESC:
		clear();
		cout << "Returning to the game, get ready" << endl;;
		Sleep(2000);
		clear();
		board.printScreen();
		break;
	case (int)GameConfig::eKeys::EXIT:
		clear();
		cout << "Finished game, Thank you for playing :D" << endl;;
		cout << "*-*-*-*-*-*-*-* Ofri & Or *-*-*-*-*-*-*-*" << endl << endl;
		stopGame = true;
		break;
	}
}

void Game::setGameStatus() {
	switch (keyPressed)
	{
	case (int)GameConfig::eKeys::ESC:
		clear();
		pauseMenu();
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

void Game::play() 
{
		LocationInfo& objectLocation = ships[activeShip].checkNextObjLocation((GameConfig::eKeys)keyPressed);
        if ((board.checkCollision(objectLocation, (GameConfig::eKeys)keyPressed)))
		{
			ships[activeShip].move((GameConfig::eKeys)keyPressed);
		}
	    size_t i = 0;
	    while (blocks[i].getSymbol()) 
	    {
		blocks[i].fallDown();
		i++;
	    }
}


void Game::afterDeath() {
	clear();
	cout << "!-!-!-!-!-!-!-! Sorry for that, Maybe try again !-!-!-!-!-!-!-!" << endl;
	health.decreaseLife();
	this->timeOver = false;
	Sleep(3000);
	clear();
	if (health.isAlive()) {
		resetBoard();
		health.printHealth();
		this->running = false;
		
		//clean all clicks fron last round
		while (_kbhit())
			_getch();
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
		
		if (_kbhit())
			setKey(_getch());
		setGameStatus();
		if (running) {
			play();
			timeOver = time.checkAndupdateTime();
		}
		Sleep(gameSpeed);
		if (timeOver)
			afterDeath();
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::WHITE);
	
}