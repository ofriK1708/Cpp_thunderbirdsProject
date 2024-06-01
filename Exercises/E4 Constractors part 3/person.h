#pragma once

#include <iostream>
using namespace std;


class Person
{
	char* name;
	double age;
	int id;
	mutable int canDriveCounter = 0;

	static double licenseAge;
	static int idGenerator;
	static int alivePersons;

	static const int START_ID = 1000;



public:
	static const int ADULT_AGE = 18;

	Person(const char* name, double age);
	Person(const Person& other);
	Person(Person&& other);

	Person& operator=(const Person& other) = delete;


	~Person();

	bool canDrive() const;

	friend ostream& operator<<(ostream& os, const Person& obj);

	static void setLicenseAge(double newAge);
	static double getLicenseAge() { return licenseAge; }
	static int getNumOfPersons() { return alivePersons; }
};