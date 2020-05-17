#include "Shop.h"

Shop::Shop(int *energy)
	:curEnergy(energy), itemNum(0)
{
	for (int idx = 0; idx < ITEM_NUM; idx++)
	{
		itemCountList[idx] = 0;
	}
}

Item* Shop::sell(int idx)
{
	Item* tempItem = NULL;
	if (0 <= idx && idx < itemNum) {
		tempItem = itemList[idx];
	} 
	else {
		return NULL;
	}

	// 에너지가 충분한지 확인한다.
	if (*curEnergy >= tempItem->price)
	{
		itemCountList[idx] = tempItem->count;
		*curEnergy -= tempItem->price;
		return itemList[idx];
	}
	else
	{
		return NULL;
	}
}

Item* Shop::getItem(int idx)
{
	if (idx < itemNum)
	{
		return itemList[idx];
	}
	else
	{
		return NULL;
	}
}

void Shop::addItem(Item* item)
{
	itemList[itemNum] = item;
	item->count = 0;
	itemNum++;
}

void Shop::addItem(Item* item, int count)
{
	itemList[itemNum] = item;
	item->count = count;
	itemNum++;
}

bool Shop::isAvailable(int idx) {
	if (idx >= itemNum) // idx가 범위를 초과했을 경우
	{ 
		return false;
	}

	if (*curEnergy < itemList[idx]->price) // 소지 에너지가 부족한 경우
	{ 
		return false;
	}

	if (itemCountList[idx] > 0) // 재사용 대기 시간이 남은 경우
	{
		return false;
	}

	return true;
}


void Shop::update()
{
	for (int idx = 0; idx < ITEM_NUM; idx++)
	{
		if (itemCountList[idx] > 0)
		{
			itemCountList[idx] -= 1;
		}
	}
}

void Shop::start()
{
}

void Shop::draw()
{
}
