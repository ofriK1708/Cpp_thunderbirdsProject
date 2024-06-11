#include "smartReadFile.h"
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
}

void smartReadFile::open(const char* fileName)
{
	if (file.is_open())
		throw std::exception("shouldnt open opened file");
	file.open(fileName, std::ios::in);
}