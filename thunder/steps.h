#pragma once
#include "GamePlay.h"

class Steps :public GamePlay{
	const string stepsEnding = ".steps";


public:
	Steps() { ending = stepsEnding; }
	void writeStep(string step);

};

