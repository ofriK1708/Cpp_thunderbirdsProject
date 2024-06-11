#pragma once


struct gameState {
	virtual ~gameState() = default;
};

class StepInput
{
	/**
	* Acstract Base class for the key inputs for the game
	*/

public:
	virtual bool hasInput() const = 0;
	virtual char getAction(gameState *state) const = 0;
	virtual ~StepInput() = default;
};
