#pragma once

#include "Define.h"

class GameObject
{
public:
	int pos[2]; // 0 : row, 1 : col
	char tag;
	bool isActive;

	GameObject();
	virtual void start() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};

