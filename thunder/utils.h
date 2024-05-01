#ifndef UTILS_H
#define UTILS_H

#include <windows.h> // for gotoxy
#include <process.h> // for system
#include "gameConfig.h"
#include <iostream>
using namespace std;


void gotoxy(int, int);
void setTextColor(GameConfig::Color color);
void hideCursor();
void clrscr();

struct Coord {
	int x = -1;
	int y = -1;
};

#endif // __GENERAL_H