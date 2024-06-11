#pragma once
#include "StepInput.h"

#include <conio.h>


class KeyboardInput : public StepInput
{
public:
	virtual char getAction(gameState *state) const override {return _getch();}
	virtual bool hasInput() const override {return _kbhit();}
};

