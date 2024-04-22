#include <iostream>
#include <string.h>
 

using namespace std;


#define NAME_LEN 21

const unsigned int SINGLE = 0, MERRIED = 1, RELATIONSHIP = 2;

struct Survivor {
	char survivorName[NAME_LEN];
	unsigned int age;
	unsigned int familyStatus;
};



void initSurvivor(Survivor& survivor) {
	
	cout << "insert survivor's name" << endl;
	cin >> survivor.survivorName;
	cout << "insert age" << endl;
	cin >> survivor.age;
	cout << "insert family status" << endl;
	cin >> survivor.familyStatus;
}

void initSurvivor(Survivor& survivor, const char name[NAME_LEN], unsigned int age, unsigned int status=SINGLE) {

	strcpy_s(survivor.survivorName, name);
	survivor.age = age;
	survivor.familyStatus = status;
}

void printSurvivor(const Survivor& survivor) {
	
	cout << survivor.survivorName << " " << survivor.age << " " << survivor.familyStatus << endl;
}

void main() {
	Survivor survivors[3] = { 0 };
	initSurvivor(survivors[0]);
	initSurvivor(survivors[1], "surviver2", 20, MERRIED);
	initSurvivor(survivors[2], "surviver3", 30);

	for (const Survivor& sur : survivors) {
		printSurvivor(sur);
	}
}


class Tribe {
	
public: 
	static const int MAX_NAME_SIZE = 21;

private:
	char name[MAX_NAME_SIZE];
	unsigned int maxSurvivors;
	Survivor** survivors;
	unsigned int numOfSurvivors;

public:
	void init(char *name, unsigned int maxSurvivors) {
		strcpy(this->name, name);
		this->maxSurvivors = maxSurvivors;
		this->numOfSurvivors = 0;
		this->survivors = new Survivor* [maxSurvivors];
	}
};









