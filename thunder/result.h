#pragma once
#include "gameConfig.h"
#include "GamePlay.h"

#include <string>

using std::string;


class Result : public GamePlay
{
	const string resultEnding = ".result";


public:
	Result() { ending = resultEnding; }
	void writeEvent(string event);
};

