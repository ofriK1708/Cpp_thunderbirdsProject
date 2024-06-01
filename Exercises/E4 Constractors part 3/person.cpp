#pragma warning(disable: 4996)
#include "person.h"

#include <cstring>
#include <iostream>
using namespace std;

double Person::licenseAge = 17.0;
int Person::idGenerator = START_ID;
int Person::alivePersons = 0;


Person::Person(const char* name, double age) :age(age), id(++idGenerator)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	alivePersons++;
}

Person::Person(const Person& other) :age(other.age), id(++idGenerator)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	alivePersons++;
}

Person::Person(Person&& other) :age(other.age), id(++idGenerator)
{
	std::swap(name, other.name);
	alivePersons++;
}

Person::~Person()
{
	delete[] name;
	alivePersons--;
}

void Person::setLicenseAge(double newAge)
{
	licenseAge = newAge;
}

ostream& operator<<(ostream& os, const Person& obj)
{
	os << obj.id << ") " << obj.name << "'s age is " << obj.age << " and he can";
	if (obj.age < Person::licenseAge)
		os << "'t";

	os << " drive";

	return os;
}

bool Person::canDrive() const
{
	canDriveCounter++;

	return age >= licenseAge;
}

