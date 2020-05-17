#pragma once
#include "Item.h"

class Remover : public Item
{
public:
	Remover(int id, char symbol, int price);
	Remover* create();
	void update();
	void draw();
	void start();
	void removeItems();
};

