#include "game.h"
#include "mapsfiles.h"
#include "utils.h"
#include "GameSleep.h"
#include "GamePrint.h"

#include <stdlib.h>
#include <iostream>
#include <Windows.h>


void Game::setMode(GameMode _mode, StepInput* _stepsInput, StepsIO* _stepsOutPut) {
	mode = _mode;
	stepInput = _stepsInput;
	switch (mode) {
	case GameMode::SIMPLE:
		break;
	case GameMode::SAVE_TO_FILE:
		resultIO.setMode(ResultIO::FileMode::write);
		stepsOutPut = _stepsOutPut;
		stepsOutPut->setMode(StepsIO::FileMode::write);
		break;
	case GameMode::LOAD_FROM_FILE:
		break;
	case GameMode::SILENT_LOAD_FROM_FILE:
		resultIO.setMode(ResultIO::FileMode::read);
		break;
	default:
		throw std::exception("Game mode is invalid");
	}
}


void Game::prepareToStart()
{
	resetBoard();
	levels = board.getNumOfLevels();
	if (mapfileLoaded) {
		health = board.getHealth();
	}
	else {
		throw std::exception("Could not load game map");
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
	if(level < levels)
	{
		level++;
		resetBoard();
		health.printHealth();
		freezeSips = true;
		keyPressed = 0;
	}
	else {
		GamePrint::print("*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*  YOU WON!!!!!  *-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
		printCredits();
	}

}

void Game::printCredits()
{
	GamePrint::print("Finished game, Thank you for playing :D");
	GamePrint::print("*-*-*-*-*-*-*-* Ofri & Or *-*-*-*-*-*-*-*\n");
}

void Game::ShipAction() 
{
	if(ships[0].GetFinishStatus() && ships[1].GetFinishStatus()) // if the player sussecfuly finished the level 
	{
		if(level == levels) // if we are at the last level and win 
			gameState = GameState::WIN;
		if (getMode() == GameMode::SAVE_TO_FILE)
			resultIO.writeEvent(time.getTimeLeft(), Events::FINISH_LEVEL);
		else if (getMode() == GameMode::SILENT_LOAD_FROM_FILE) {
			if (!resultIO.cmpEvents(time.getTimeLeft(), Events::FINISH_LEVEL)) {
				gameState = GameState::RESULT_DIFF;
			}
		}
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
	if (getMode() == GameMode::SAVE_TO_FILE) {
		resultIO.writeEvent(time.getTimeLeft(), Events::DEATH);
		stepsOutPut->writeStep('0', 0);
	}
	else if (getMode() == GameMode::SILENT_LOAD_FROM_FILE) {
		if (!resultIO.cmpEvents(time.getTimeLeft(), Events::DEATH)) {
			gameState = GameState::RESULT_DIFF;
		}
	}
	if (health.getlivesLeft() > 1)
	{
		 clrscr();
		 GamePrint::print("!-!-!-!-!-!-!-! Sorry for that, try again :) !-!-!-!-!-!-!-!");
		 health.decreaseLife();
		 this->timeOver = false;
		 GameSleep::longSleep();
		 clrscr();
	
		 resetBoard();
		 health.printHealth();
		 freezeSips = true;
		 keyPressed = 0;
	}
	else
	{
		clrscr();
		GamePrint::print("!-!-!-!-!-!-!-!-!-!-!-!-!-!-!-! GAME OVER !-!-!-!-!-!-!-!-!-!-!-!-!-!-!-!");
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
		try {
			if (stepInput->hasInput()) {
				setKey(stepInput->getAction());
				if (mode == GameMode::SAVE_TO_FILE) {
					stepsOutPut->writeStep(keyPressed, time.getTimeLeft());
				}
			}
			ShipAction();
			if (gameState == GameState::RUNNING)
			{
				play();
				timeOver = time.checkAndupdateTime();
				health.printHealth();
			}

			GameSleep::gameOprSleep();
			if (timeOver)
				afterDeath();
		}
		catch (const std::ios_base::failure& e) {
			time.reverse();
			setKey((int)GameConfig::eKeys::ESC);
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::WHITE);
}