#include "GamePlay.h"


GameConfig::ErrorCode GamePlay::closeCurrFile() {
	auto res = GameConfig::Success;
	
	if (file.is_open()){
		file.flush();
		file.close();
	}

	if (file.is_open()) {
		res = GameConfig::Failed;
	}

	return res;
}

GameConfig::ErrorCode GamePlay::openFile(size_t level) {
	auto res = GameConfig::Success;

	closeCurrFile();
	file.open(prefix + std::to_string(level) + ending, std::ofstream::out | std::ofstream::app);
	
	if (!file) {
		std::cout << "Error opening file!" << std::endl;
		res = GameConfig::Failed;
	}

	return res;
}


void GamePlay::write(string data) {
	file << data << std::endl;
}
