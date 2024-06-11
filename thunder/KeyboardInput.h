#pragma once
#include "UserInput.h"

#include <conio.h>


class KeyboardInput : public UserInput
{
public:
	virtual char getAction(gameState *state) const override {return _getch();}
};

