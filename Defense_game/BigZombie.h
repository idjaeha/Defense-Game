#pragma once
#include "Zombie.h"

class BigZombie : public Zombie
{
public:
	BigZombie(int idx, list<GameObject*>* activeGameObjectList, char** canvas, int* hp);
	void start();
	void update();
	void move();
	void attack();
};

