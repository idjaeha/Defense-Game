#pragma once
#include "Zombie.h"

class NormalZombie : public Zombie
{
public:
	NormalZombie(int idx, list<GameObject*>* activeGameObjectList, char** canvas, int* hp);
	void start();
	void update();
	void move();
	void attack();
};

