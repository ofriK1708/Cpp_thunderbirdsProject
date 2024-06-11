#pragma once
#include "GamePlay.h"

class Steps :public GamePlay{
	const string stepsEnding = ".steps";


public:
	Steps() { ending = stepsEnding; }
	void writeStep(size_t step, size_t timeLeft);

};
