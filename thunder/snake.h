#ifndef SNAKE_H
#define SNAKE_H

#include "point.h"

class Snake
{
private:
	Point body[7];
	char ch;
	int backgroundcolor;
public:
	void init(const Point& head, char ch, int color);
	void move(GameConfig::eKeys direction);
	//bool checkCollision(int x, int y); // placed here for a lack of better option, would move in the future
};

#endif
