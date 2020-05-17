#pragma once

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <list>
#include <string>

using namespace std;

// Position
#define POSITION_ENERGE			2
#define POSITION_FLOWER			10
#define POSITION_SHOOTER		16
#define POSITION_BOMB			22
#define POSITION_SHIELD			28
#define POSITION_REMOVER		34

// Character
// 1 ~ 50의 값은 숫자로 사용하므로 사용되지 않는다.
// 해당 범위에 포함하는 값 중에 유효한 값은 '0' = 48, '1' = 49, '2' = 50 이 존재한다.
#define CHAR_SUNFLOWER			'S'
#define CHAR_POTATO				'P'
#define CHAR_SHIELD				'D'
#define CHAR_SHOOTER			'T'
#define CHAR_REMOVER			'R'
#define CHAR_ENERGY				'E'
#define CHAR_BLANK				'B'
#define CHAR_WALL				'W'
#define CHAR_ITEM				'I'
#define CHAR_ZOMBIE				'Z'
#define CHAR_ZOMBIE_NORMAL		'N'
#define CHAR_ZOMBIE_BIG			'M'
#define CHAR_BULLET				'O'

// Size
#define MAP_SIZE_ROW			5
#define MAP_SIZE_COL			50
#define CANVAS_SIZE_ROW			3
#define CANVAS_SIZE_COL			29
#define CANVAS_START_ROW		1
#define CANVAS_START_COL		20

// ETC
#define ROW						0
#define COL						1
#define ITEM_NUM				5
#define CURSOR_NUM				2
#define BULLET_NUM				50

//KEY
#define KEY_ENTER				13		
#define KEY_ESC					27			
#define KEY_ARROW_1				224
#define KEY_ARROW_RIGHT			77
#define KEY_ARROW_LEFT			75

//Zombie
#define ZOMBIE_NORMAL			1
#define ZOMBIE_BIG				2

void gotoxy(int x, int y);
void gotoxy(int x, int y, const char msg[]);
void gotoxy(int x, int y, int number);
int createRandomNumber();