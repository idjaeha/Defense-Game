#pragma once
#include "GameObject.h"
#include "Item.h"

class Shop : public GameObject
{
public:
	Shop(int* energy);
	Item* itemList[ITEM_NUM];
	int* curEnergy;
	int itemCountList[ITEM_NUM];
	int itemNum;
	Item* sell(int idx);
	Item* getItem(int idx);
	void addItem(Item* item);
	void addItem(Item* item, int count);
	bool isAvailable(int idx);
	void update();
	void start();
	void draw();
};

