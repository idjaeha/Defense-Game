// main.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "GameManager.h"


int main()
{
	GameManager *gameManager = new GameManager();
	gameManager->startGame();
	gotoxy(0, 10);
	printf("\n정상적으로 종료되었습니다.\n");
	return 0;
}




