#pragma once
#include "GameObject.h"
#include "NormalZombie.h"
#include "BigZombie.h"

class Spawner : public GameObject
{
public:
	int spawnNormalCount;
	int spawnBigCount;
	int startCount;
	int* hp;
	char** canvas;
	list<GameObject*>* activeGameObjectList;
	Spawner(char** canvas, list<GameObject*>* activeGameObjectList, int* hp);
	void start();
	void update();
	void draw();
	void spawn(int id);
};

