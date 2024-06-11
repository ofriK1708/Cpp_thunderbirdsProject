#include "steps.h"
#include "gameConfig.h"
#include <string>

using std::to_string;

void Steps::writeStep(size_t step, size_t timeLeft)
{
	string space = " ";
	string message = to_string(step) + space + to_string(timeLeft);
	if (GameConfig::isShipControlMove((GameConfig::eKeys)step))
		write(message);
}
