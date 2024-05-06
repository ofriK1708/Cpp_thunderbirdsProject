#include "health.h"

#include "utils.h"



bool Health::isAlive() 
{
	if (livesLeft <= 0)
		return false;
	return true;
}




void Health::printHealth() {
	gotoxy(x + GameConfig::MIN_X, y + GameConfig::MIN_Y);

	cout << "Remaining Lives: ";
	
	if (isColor)
		setTextColor(GameConfig::LIGHTRED);
 
	std::cout << this->livesLeft;

	setTextColor(GameConfig::WHITE);
	hideCursor();
}