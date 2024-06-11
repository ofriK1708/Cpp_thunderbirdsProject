#pragma once

class Time
{
	int x;
	int y;
	int totalTime;
	int timeLeft;
	char timeSymbol;
	bool isColor = false;

public:
	const int& getTimeLeft() const { return timeLeft;}
	void setLocation(int x, int y) { this->x = x; this->y = y; }
	void setTimeSettings(const int totalTime, const bool isColor);
	bool checkAndupdateTime();
	void resetTime() { timeLeft = totalTime; }
	void printTime(int time);
};

