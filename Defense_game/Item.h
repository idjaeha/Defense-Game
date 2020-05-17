#pragma once
#include "GameObject.h"

class Item : public GameObject
{
public:
	int id;					// Item의 고유 id
	int life;				// ltem의 수명을 나타냄
	char symbol;			// Item의 character 값
	const char *sprite;		// Item의 sprite
	int count;				// Item의 쿨타임
	int price;				// Item의 가격
	char** canvas;			// Item에 연결된 canvas
	int canvasColPos;		// Item의 canvas 내의 위치
	Item(int id, char symbol, int price);
	list<GameObject*>* activeGameObjectList;
	virtual Item* create() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void start() = 0;
};

