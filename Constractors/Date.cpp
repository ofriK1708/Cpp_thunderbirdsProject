#include <iostream>
#include <cstring>

#include "Date.h"


Date::Date(size_t day, size_t month, size_t year, const char* whatSpecial){
	this->day = day;
	this->month = month;
	this->year = year;
	this->whatSpecial = _strdup(whatSpecial);

	print();
}

void Date::setOcasion(const char* str) {
	delete whatSpecial;
	whatSpecial = _strdup(str);
}

void Date::print() {
	std::cout << day << ", " << month << ", " << year << ": " << whatSpecial << std::endl << std::endl;
}

