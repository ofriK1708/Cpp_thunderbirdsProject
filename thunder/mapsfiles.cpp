#include "mapsfiles.h"
#include <iostream>
#include <fstream>
#include "utils.h"
#include "Windows.h"
#include <filesystem>
#include "gameConfig.h"
#include "GameSleep.h"
#include "GamePrint.h"


using std::endl;
using std::cin;
using std::string;

void Mapsfiles::loadMapLevels()
{
	for(const auto& file : std::filesystem::directory_iterator(filesPath))
	{
     if(file.is_regular_file()) // check if it's a file and not a dir or something else
	 {
		 string currFileName = file.path().filename().string();
		 // now checks if .screen.txt is at the end of the file name and there is some name before the .screen.txt
		 if ((currFileName.size() > fileSuffix.size()) && ((currFileName.substr(currFileName.size() - fileSuffix.size())) == fileSuffix))
		 {
			 filesNames.push_back(currFileName);
		 }
		 
	 }
	}
	std::sort(filesNames.begin(), filesNames.end());// sorting the fileNames lexicographically
	mapsLoaded = true;
}

void Mapsfiles::GetUserFileChoice()
{
	do
	{
		if (fileIndex != 0) // not the first time we entred this loop
			GamePrint::print("invalid choice, try again");
		GamePrint::print("Please Enter your file choice(enter a number):");
		for (int i = 0; i < filesNames.size(); i++)
			GamePrint::print(to_string(i + 1) + ": " + (string)filesNames[i]);
		cin >> fileIndex;
	} while (fileIndex > filesNames.size() || fileIndex < 1);
	fileIndex--;
	
}
bool Mapsfiles::getMap(char map[][GameConfig::GAME_WIDTH + 1], bool userChoice)
{
	if (filesNames.size() == 0) 
	{
		GamePrint::print("couldn't find any maps files, please enter a map file in the diractory - mapFiles");
		return false;
	}
	if (userChoice)
		GetUserFileChoice();
	if (currlevelLoaded) {
		return true;
	}
	currfileName = filesPath + "/" + filesNames[fileIndex];
	GameSleep::systemOprSleep();
	clrscr();
	fileMap.open(currfileName);
	checkFileStatus();

	if (fileStatus)
	{
		string line;
		size_t j;
		for (size_t i = 0; i < GameConfig::GAME_HEIGHT; i++)
		{
			getline(fileMap.getFile(), line);
			for (j = 0; j < GameConfig::GAME_WIDTH && j < line.length(); j++)
			{
				map[i][j] = line[j];
			}
			for (; j < GameConfig::GAME_WIDTH; j++)
				map[i][j] = GameConfig::WALL_SYMBOL;

			map[i][j] = '\0';
		}
		if (!checkMapAndUpdate(map))
		{
			GamePrint::print("couldn't load map,map is not correct, please try to fix it or choose another level");
			return false;
		}
		currlevelLoaded = true;
		return true;
	}
	return false;
}

bool Mapsfiles::checkMapAndUpdate(char map[][GameConfig::GAME_WIDTH + 1])
{
	unsigned int bigShipSize = 0;
	unsigned int smallShipSize = 0;
	unsigned int numOfLegend = 0;
	for(size_t line = 0; line < GameConfig::GAME_HEIGHT;line++)
	{
		for(size_t col = 0; col < GameConfig::GAME_WIDTH;col++)
		{
			switch (map[line][col])
			{
			case GameConfig::BIG_SHIP_S:
				bigShipSize++;
				break;
			case GameConfig::SMALL_SHIP_S:
				smallShipSize++;
				break;
			case '&':
				if (numOfLegend == 0)
					copyHeaderToMap(map, line, col);
				numOfLegend++;
				break;
			}
		}
	}
	if (bigShipSize == 4 && smallShipSize == 2 && numOfLegend == 1)
		return true;
	return false;
}

void Mapsfiles::copyHeaderToMap(char map[][GameConfig::GAME_WIDTH + 1],size_t& line, size_t& col)
{
	for(int i = 0; i < 3; i++)
	{
		for(col = 0; col < GameConfig::GAME_WIDTH;col++)
		{
			map[line][col] = legend[i][col];
		}
		map[line][col] = '\0';
		line++;
	}
}

void Mapsfiles::checkFileStatus()
{
	if (fileMap.is_open() && !fileMap.bad())
	{
		fileStatus = true;
	}
	else
	{
		GamePrint::print("Problem opening file!!!!");
		fileStatus = false;
	}
}
void Mapsfiles::loadNextMap()
{
/*
	if (fileMap.is_open())
		fileMap.close();*/
	currfileName = filesNames[++fileIndex];
	currlevelLoaded = false;
}


