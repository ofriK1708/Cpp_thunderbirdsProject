#include "smartReadFile.h"

#include <string>

void smartReadFile::close() {
	if (file.is_open()) {
		file.close();
	}
}


smartReadFile& smartReadFile::operator=(const smartReadFile& other) 
{
	if (this != &other) 
	{
		if (other.file.is_open()) 
		{
			throw std::exception("cannot assign with opened file");
		}
		if (file.is_open()) 
		{
			file.close();
		}
	}
	return *this;
}
void smartReadFile::open(const std::string& fileName)
{
	if (file.is_open())
		throw std::exception("shouldnt open opened file");
	file.open(fileName, std::ios::in);
	if (not file.is_open())
		throw std::exception("could not open the file");
	else if(file.bad())
		throw std::exception("could not open the file");
}

void smartReadFile::open(const char* fileName)
{
	open((std::string)(fileName));
}