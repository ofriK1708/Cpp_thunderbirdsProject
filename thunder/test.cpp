#include "test.h"
#include "utils.h"

void testKbhitAndGetch()
{
	while (true)
	{
		cout << "Waiting for key\n";
		if (_kbhit())
		{
			char pressedChar = _getch();
			cout << pressedChar << " key was pressed\n";

		}
		cout << "another iteration\n";
		Sleep(200);
	}
}


void movingKey(char key)
{
	int x = 1, y = 1;

	while (!_kbhit() || _getch() != 27)
	{
		gotoxy(x, y);
		cout << key;
		Sleep(-2);
		gotoxy(x, y);
		cout << x;

		++x;
		if (x == 80)
			x = 1;

		++y;
		if (y == 25)
			y = 1;

	}
}