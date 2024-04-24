#include "ship.h"

void Ship::init(const Point& head, char symbol, int color)
{
	this->symbol = symbol;
	this->backgroundcolor = color;
	pos[0] = head;
	pos[0].draw(symbol, backgroundcolor);
	for (int i = 1; i < 7; i++)
	{
		pos[i] = pos[i - 1];
		pos[i].move((GameConfig::eKeys)0);
		pos[i].draw(symbol, backgroundcolor);
	}
}
void Ship::move(GameConfig::eKeys direction)
{
	pos[6].draw(' ', GameConfig::COLORS[0]);
	for (int i = 6; i > 0; i--)
	{
		pos[i] = pos[i - 1];
	}
	pos[0].move(direction);
	pos[0].draw(symbol, backgroundcolor);
}
