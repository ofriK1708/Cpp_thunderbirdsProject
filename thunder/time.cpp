#include "time.h"
#include "iostream"
#include "utils.h"
#include "gameConfig.h"
void Time::setTimeSettings(const int totalTime, const bool isColor)
{
	this->totalTime = timeLeft = totalTime;
	this->isColor = isColor;
	printTime(totalTime / 10);
}

bool Time::checkAndupdateTime()
{
	timeLeft--;
	if (timeLeft <= 0)
	{
		resetTime();
		return true;
	}
	else
	{
		if (timeLeft % 10 == 0)
			printTime(timeLeft / 10);
		return false;
	}
}

void Time::printTime(int time)
{
	gotoxy(x + GameConfig::MIN_X, y + GameConfig::MIN_Y);
	cout << "Time Left : ";
	if (isColor)
		setTextColor(GameConfig::GREEN);

	
	// Print updated time
	for (int i = 0; i < time; i++)
	{
		std::cout << "|";
	}

	// Overwrite the remaining characters with spaces
	for (int i = time; i < (totalTime / 10); i++)
	{
		std::cout << " ";
	}
	setTextColor(GameConfig::WHITE);
	hideCursor();
}