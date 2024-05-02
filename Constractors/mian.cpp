#include "date.h"

void main() {
	Date d1(7, 4, 1999, "wowowo");
	Date d2(d1);

	d1.setDay(20);
	d1.setOcasion("jkjkj");

	d1.print();
	d2.print();
}