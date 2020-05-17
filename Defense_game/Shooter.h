#pragma once
#include "Item.h"
#include "Bullet.h"

class Shooter : public Item
{
public:
	int shootCount;
	Shooter(int id, char symbol, int price);
	Shooter* create();
	Bullet bullets[BULLET_NUM];
	list<Bullet*> activeBullets;
	void start();
	void update();
	void updateBullets();
	void deleteBullets();
	void drawBullets();
	void draw();
	Bullet* getBullet();
};

