#pragma once
#include "Item.h"

class Energy : public Item
{
public:
	Energy();
	Energy(int idx, bool isActive, char** canvas);
	void start();
	void draw();
	void update();
	Energy* create();
};

