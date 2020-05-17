#include "Define.h"

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void gotoxy(int x, int y, const char msg[]) {
	gotoxy(x, y);
	printf(msg);
}

void gotoxy(int x, int y, int num) {
	gotoxy(x, y);
	printf("%4d", num);
}

int createRandomNumber()
{
	// 0 ~ 32767 사이의 수를 얻는다.
	srand((unsigned int)time(0));
	return rand();
}
