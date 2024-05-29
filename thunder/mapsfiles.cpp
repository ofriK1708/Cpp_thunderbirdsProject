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
		int j;
		for (int i = 0; i < GameConfig::GAME_HEIGHT; i++)
		{
			getline(fileMap,line);
			for (j = 0; j < GameConfig::GAME_WIDTH; j++)
			{
				if(line[j] != '&')
					map[i][j] = line[j];
				else
				{
					copyHeaderToMap(map,i);
					i += 2;
					break;
				}
			}
			if( j == GameConfig::GAME_WIDTH)
			{
				map[i][j] = '/0';
			}
		}
	}
}

void Mapsfiles::copyHeaderToMap(char map[][GameConfig::GAME_WIDTH + 1],int line)
{
	int j;
	for(int i = 0; i < 3;i++)
	{
		for(j = 0; j < GameConfig::GAME_WIDTH; j++)
		{
			map[line + i][j] = legend[i][j];
		}
		map[line + i][j] = '/0';
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

