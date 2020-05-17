#pragma once
#include "GameObject.h"
#include "Item.h"

class Zombie : public GameObject
{
public:
	int* hp;
	int canvasColPos;
	int life;
	int attackCount;
	int const rawAttackCount;
	int moveCount;
	int const rawMoveCount;
	char symbol;
	list<GameObject*>* activeGameObjectList;
	char** canvas;
	virtual void start() = 0;
	virtual void update() = 0;
	Zombie(list<GameObject*>* activeGameObjectList, char** canvas, int rawMoveCount, int rawAttackCount, int* hp);
	void draw();
	GameObject* searchShield();
};

