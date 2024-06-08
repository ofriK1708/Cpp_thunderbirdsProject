#include "result.h"

#include <string>

void Result::writeEvent(int timeLeft, Events event) {
	string message;
	
	switch (event) {
	case Events::DEATH:
		message = "death";
	case Events::FINISH_LEVEL:
		message = "finish";
	}
	message.append(" ");
	message.append(std::to_string(timeLeft));
	
	write(message);
}