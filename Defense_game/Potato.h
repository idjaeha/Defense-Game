#pragma once
#include "Item.h"
#include "Zombie.h"

class Potato : public Item
{
public:
	Potato(int id, char symbol, int price);
	Potato* create();
	void update();
	void draw();
	void start();
	void killZombies();
};

