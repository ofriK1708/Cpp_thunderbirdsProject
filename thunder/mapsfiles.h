#pragma once
#include <string>
#include "gameConfig.h"
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>
using std::string;
using std::ifstream;
using std::vector;
using std::exception;


class SmartFile {
	ifstream file;
public:
	~SmartFile() {
		if (file.is_open())
			file.close();
	}
	MyFile& operator=(const MyFile& other) {
		if (this != &other) {
			if (other.file.is_open()) {
				throw std::exception("cannot assign with opened file");
			}
			if (file.is_open()) {
				file.close();
			}
		}
		return *this;
	}
	MyFile(const MyFile&) = delete;
	MyFile() {}
	void open(const string& fileName) {
		if (file.is_open())
			throw std::exception("shouldnt open opened file");
		file.open(fileName, std::ios::in);
	}
	ifstream& getFile() { return file; }
	bool is_open() const { return file.is_open(); }
	bool bad() const {return file.bad();}
};

class Mapsfiles
{
	char legend[3][GameConfig::GAME_WIDTH + 1] = {
		"W T                                                       WWWW            W    W",
		"W                                                         WBBW           WSW   W",
		"W L                                                       WBBW           WSW   W"
	};
	vector<string> filesNames;
	size_t fileIndex = 0;
	string filesPath = "mapFiles";
	string currfileName;
	string fileSuffix = ".screen.txt";
	bool fileStatus = false;
	bool mapsLoaded = false;
	bool currlevelLoaded = false;
	MyFile fileMap;
	void checkFileStatus();
	void copyHeaderToMap(char map[][GameConfig::GAME_WIDTH + 1],size_t& line,size_t& col);
	bool checkMapAndUpdate(char map[][GameConfig::GAME_WIDTH + 1]);
	void GetUserFileChoice();
	void loadNextMap();
	
public:
	void loadMapLevels();
	//~Mapsfiles();
	bool getMap(char map[][GameConfig::GAME_WIDTH + 1],bool userChoice);
	bool getMapsLoadedstatus() const { return mapsLoaded; }
	bool getCurrLevelLoadedStatus() const { return currlevelLoaded; }

	
};

