#pragma once
#include <stdio.h>
#include <fstream>
#include <string>
class smartReadFile {
	std::ifstream file;
public:
	~smartReadFile() {
		if (file.is_open())
			file.close();
	}
	smartReadFile& operator=(const smartReadFile& other);
	smartReadFile(const smartReadFile&) = delete;
	smartReadFile() {}
	void open(const std::string& fileName);
	void open(const char* fileName);
	bool is_open() const { return file.is_open(); }
	bool bad() const { return file.bad(); }
	std::ifstream& getFile() { return file; }
};