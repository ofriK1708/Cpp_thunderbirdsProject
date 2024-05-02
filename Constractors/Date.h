#pragma once

class Date {
	size_t day;
	size_t month;
	size_t year;

	char *whatSpecial;

public:
	void setDay(size_t day) { this->day = day; }
	void setOcasion(const char* str);
	Date(size_t day, size_t month, size_t year, const char* whatSpecial);
	void print();


};