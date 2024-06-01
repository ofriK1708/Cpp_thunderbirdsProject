#include "person.h"

#include <iostream>
using namespace std;

int main()
{
	cout << "There are currently " << Person::getNumOfPersons() << " persons alive\n";
	cout << "The license age is " << Person::getLicenseAge() << endl;
	std::cout << "Adult is from age " << Person::ADULT_AGE << endl;

	cout << "Creating 2 persons as PTRs\n";
	Person* ptrP1 = new Person("John", 16.5);
	Person* ptrP2 = new Person("Doe", 20.0);

	cout << *ptrP1;
	cout << endl;
	cout << *ptrP2;
	cout << endl;

	cout << "There are currently " << Person::getNumOfPersons() << " persons alive\n";

	cout << "Deleting ptrP1 & ptrP2\n";
	delete ptrP1;
	delete ptrP2;

	cout << "There are currently " << Person::getNumOfPersons() << " persons alive\n";

	{
		cout << "Creating p1 and p2(p1) in a block" << endl;
		Person p1("gogo", 16);
		Person p2(p1);
		cout << "There are currently " << Person::getNumOfPersons() << " persons alive\n";
		cout << p1;
		cout << endl;
		cout << p2;
		cout << endl;
		cout << "Exit the block" << endl;
	}

	{
		cout << "There are currently " << Person::getNumOfPersons() << " persons alive\n";

		const Person p3("Dan", 20);
		cout << "Dan " << (p3.canDrive() ? "Can" : "Cant") << " Drive" << endl;

		Person::setLicenseAge(1000);

		cout << "Dan " << (p3.canDrive() ? "Can" : "Cant") << " Drive" << endl;
	}

	cout << "There are currently " << Person::getNumOfPersons() << " persons alive\n";

	{
		cout << "Creating p4 and p5(std::move(p4)) in a block" << endl;
		cout << "There are currently " << Person::getNumOfPersons() << " persons alive\n";

		Person p4("temp", 16);
		Person p5(std::move(p4));

		cout << "There are currently " << Person::getNumOfPersons() << " persons alive\n";
		//cout << p4; //Warning	C26800	Use of a moved from object : 'p4'
		cout << p5;
		cout << endl;
	}

	cout << "There are currently " << Person::getNumOfPersons() << " persons alive\n";



	return 0;
}