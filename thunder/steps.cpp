#include "steps.h"

#include <string>

using std::to_string;

void Steps::writeStep(int step, int timeLeft) {
	string space = " ";
	string message = to_string(step) + space + to_string(timeLeft);
	write(message);
}