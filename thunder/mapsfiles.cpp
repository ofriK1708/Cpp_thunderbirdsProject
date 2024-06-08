#include "mapsfiles.h"
#include <iostream>
#include <fstream>
#include "utils.h"
#include "Windows.h"
#include <filesystem>
#include "gameConfig.h"
using std::cout;
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
			cout << "invalid choice, try again";
		cout << "Please Enter your file choice(enter a number): " << endl;
		for (int i = 0; i < filesNames.size(); i++)
			cout << i + 1 << ": " << filesNames[i] << endl;
		cin >> fileIndex;
	} while (fileIndex > filesNames.size() || fileIndex < 1);
	fileIndex--;
	
}
bool Mapsfiles::getMap(char map[][GameConfig::GAME_WIDTH + 1], bool userChoice)
{
	if (filesNames.size() == 0) 
	{
		cout << "couldn't find any maps files, please enter a map file in the diractory - mapFiles" << endl;
		return false;
	}
	if (userChoice)
		GetUserFileChoice();

	currfileName = filesPath + "/" + filesNames[fileIndex];
	Sleep(GameConfig::SYSTEM_OPR_SLEEP);
	clrscr();
	fileMap.open(currfileName, std::ios::in);
	checkFileStatus();
	
	if (fileStatus)
	{
		string line;
		size_t j;
		for (size_t i = 0; i < GameConfig::GAME_HEIGHT; i++)
		{
			getline(fileMap,line);
			for (j = 0; j < GameConfig::GAME_WIDTH && j<line.length(); j++)
			{
				map[i][j] = line[j];
			}
			for (; j < GameConfig::GAME_WIDTH; j++)
				map[i][j] = GameConfig::WALL_SYMBOL;

			map[i][j] = '\0';			
		}
		if(!checkMapAndUpdate(map))
		{
			cout << "couldn't load map,map is not correct, please try to fix it or choose another level" << endl;
			return false;
		}
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
		cout << "Problem opening file!!!!";
		fileStatus = false;
	}
}
void Mapsfiles::loadNextMap()
{
	if (fileMap.is_open())
		fileMap.close();
	fileMap.open(filesNames[++fileIndex], std::ios::in);
	checkFileStatus();
}


