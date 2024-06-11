#include "result.h"

#include <string>

void Result::writeEvent(int timeLeft, Events event) {
	string message;
	
	switch (event) {
	case Events::DEATH:
		message = "death";
		break;
	case Events::FINISH_LEVEL:
		message = "finish";
		break;
	default:
		message = "unknown";
		break;
	}
	message.append(" ");
	message.append(std::to_string(timeLeft));
	
	write(message);
}