#pragma once
#include "GameObject.h"

class Item : public GameObject
{
public:
	int id;					// Item�� ���� id
	int life;				// ltem�� ������ ��Ÿ��
	char symbol;			// Item�� character ��
	const char *sprite;		// Item�� sprite
	int count;				// Item�� ��Ÿ��
	int price;				// Item�� ����
	char** canvas;			// Item�� ����� canvas
	int canvasColPos;		// Item�� canvas ���� ��ġ
	Item(int id, char symbol, int price);
	list<GameObject*>* activeGameObjectList;
	virtual Item* create() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void start() = 0;
};

