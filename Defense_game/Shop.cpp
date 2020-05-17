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

	// �������� ������� Ȯ���Ѵ�.
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
	if (idx >= itemNum) // idx�� ������ �ʰ����� ���
	{ 
		return false;
	}

	if (*curEnergy < itemList[idx]->price) // ���� �������� ������ ���
	{ 
		return false;
	}

	if (itemCountList[idx] > 0) // ���� ��� �ð��� ���� ���
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
