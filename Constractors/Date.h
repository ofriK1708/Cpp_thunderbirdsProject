#pragma once

class Date {
	size_t day;
	size_t month;
	size_t year;

	char whatSpecial[20] = {0};

public:
	void setDay(size_t day) { this->day = day; }
	void init(size_t day, size_t month, size_t year, const char* whatSpecial);


};