#include "game.h"
#include "mapsfiles.h"
#include "utils.h"

#include <stdlib.h>
#include <iostream>
#include <Windows.h>


void Game::init()
{
	resetBoard();
	if (mapfileLoaded) {
		health = board.getHealth();
	}
}

void Game::resetBoard()
{
	board = Board();
	board.init(colorSet, mapChoose);
	mapfileLoaded = false;
	if (board.getMapFileStatus())
	{
		mapfileLoaded = true;
		ships = board.getShips();
		blocks = board.getBlocks();
		time = board.getTime();
		time.setTimeSettings(gameTime, colorSet);
	}
}


void Game::gameFinish()
{
	clrscr();
	cout << "*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*  YOU WON!!!!!  *-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
	printCredits();

}

void Game::printCredits()
{
	cout << "Finished game, Thank you for playing :D" << endl;;
	cout << "*-*-*-*-*-*-*-* Ofri & Or *-*-*-*-*-*-*-*" << endl << endl;
}

void Game::ShipAction() 
{
	if(ships[0].GetFinishStatus() && ships[1].GetFinishStatus()) // if the player sussecfuly finished the level 
	{
		gameState = GameState::WIN;
		gameFinish();
	}
	else
	{
		switch (keyPressed)
		{
		case (int)GameConfig::eKeys::ESC:
			clrscr();
			gameState = GameState::PAUSE;
			keyPressed = 0;
			break;

		case (int)GameConfig::eKeys::SWITCH_TO_BIG_S:
			if (activeShip == GameConfig::ShipID::SMALL)
				activeShip = GameConfig::ShipID::BIG;
			else
				freezeSips = true;
			break;

		case (int)GameConfig::eKeys::SWITCH_TO_SMALL_S:
			if (activeShip == GameConfig::ShipID::BIG)
				activeShip = GameConfig::ShipID::SMALL;
			else
				freezeSips = true;
			break;

		case (int)GameConfig::eKeys::UP:
		case (int)GameConfig::eKeys::DOWN:
		case (int)GameConfig::eKeys::LEFT:
		case (int)GameConfig::eKeys::RIGHT:
			freezeSips = false;
			break;
		};
	}
}

void Game::play() {
	if(not freezeSips)
		ships[activeShip].move((GameConfig::eKeys)keyPressed);
	for(auto & pair: *blocks)
		pair.second.move();
}


void Game::afterDeath() 
{
	if (health.getlivesLeft() > 1)
	{
		 clrscr();
		 cout << "!-!-!-!-!-!-!-! Sorry for that, try again :) !-!-!-!-!-!-!-!" << endl;
		 health.decreaseLife();
		 this->timeOver = false;
		 Sleep(GameConfig::LONG_SLEEP);
		 clrscr();
	
		 resetBoard();
		 health.printHealth();
		 freezeSips = true;
		 keyPressed = 0;
	}
	else
	{
		clrscr();
		cout << "!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-! GAME OVER !-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!" << endl;
		printCredits();
		gameState = GameState::LOSE;
	}
}


/**
 * Runs the game loop, handling player input.
 */
void Game::gameLoop()
{
	keyPressed = 0;

	while (gameState==GameState::RUNNING and !timeOver and health.isAlive())
	{
		if (userInput->hasInput()) {
			setKey(userInput->getAction());
			//stepsFile.writeStep(keyPressed, time.getTimeLeft());
		}
		ShipAction();
		if (gameState == GameState::RUNNING)
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