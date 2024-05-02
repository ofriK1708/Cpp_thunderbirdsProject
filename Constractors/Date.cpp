#include <iostream>
#include <cstring>

#include "Date.h"


void Date::init(size_t day, size_t month, size_t year, const char* whatSpecial) {
	this->day = day;
	this->month = month;
	this->year = year;
	strcpy_s(this->whatSpecial, whatSpecial);

	std::cout << day << ", " << month << ", " << year << std::endl;
	std::cout << whatSpecial << std::endl;
}
