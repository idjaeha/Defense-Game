#pragma once
#include "Item.h"
#include "Energy.h"

class Sunflower : public Item
{
public:
	int energyCount;
	Sunflower(int id, char symbol, int price);
	Sunflower* create();

	void start();

	void update();
	void createEnergy();
	void draw();
	
};

