#include "mapsfiles.h"
#include <iostream>
#include <fstream>
#include "utils.h"
#include "Windows.h"
using std::cout;
using std::endl;
using std::cin;
using std::string;

void Mapsfiles::GetUserFileChoice()
{
	cout << "Please Enter your file choice: " << endl;
	cout << "1. tb01.screen" << endl;
	cout << "2. tb02.screen" << endl;
	cout << "3. tb03.screen" << endl;
	cin >> userChoice;
	do
	{
		switch (userChoice)
		{
		case 1:
			fileName = "tb01.screen.txt";
			break;
		case 2:
			fileName = "tb02.screen.txt";
			break;
		case 3:
			fileName = "tb03.screen.txt";
			break;
		default:
			cout << "Invalid choice, try again" << endl;
			cout << "1. tb01.screen" << endl;
			cout << "2. tb02.screen" << endl;
			cout << "3. tb03.screen" << endl;
			break;
		}
	} while (userChoice > 3 || userChoice < 1);
	Sleep(150);
	clrscr();
	fileMap.open(fileName, std::ios::in);
	checkFileStatus();
}
void Mapsfiles::getMap(char map[][GameConfig::GAME_WIDTH + 1])
{
	if (userChoice == 0) 
	{
		searchMapFile();
	}
	if (fileStatus)
	{
		string line;
		size_t j;
		for (size_t i = 0; i < GameConfig::GAME_HEIGHT; i++)
		{
			getline(fileMap,line);
			for (j = 0; j < GameConfig::GAME_WIDTH; j++)
			{
				map[i][j] = line[j];
			}
			map[i][j] = '/0';			
		}
		if(!checkMapAndUpdate(map))
		{
			cout << "couldn't load map,map is not correct, please try to fix it or choose another level";
		}
	}
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
		map[line][col] = '/0';
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
	}
}

void Mapsfiles::searchMapFile()
{
	string baseName = "tb";

	// Check files tb01, tb02, and tb03
	for (int i = 1; i <= 3; ++i) 
	{
		fileName = baseName + "0" + std::to_string(i) + ".screen.txt";;
		fileMap.open(fileName,std::ios::in);
		checkFileStatus();
		if (fileStatus)
		{
			return;
		}
	}
	
	std::cout << "No files found (tb01, tb02, tb03)." << std::endl;
	
}

