#pragma once
#include "Item.h"

class Shield : public Item
{
public:
	Shield(int id, char symbol, int price);
	Shield* create();
	void update();
	void draw();
	void start();
};

