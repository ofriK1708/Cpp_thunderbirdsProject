#pragma once

class Time
{
	int x;
	int y;
	int timeLeft;
	int totalTime;
	char timeSymbol;
	bool isColor = false;

public:
	void setLocation(int x, int y) { this->x = x; this->y = y; }
	void setTimeSettings(const int totalTime, const bool isColor);
	bool checkAndupdateTime();
	void resetTime() { timeLeft = totalTime; }
	void printTime(int time);
};

