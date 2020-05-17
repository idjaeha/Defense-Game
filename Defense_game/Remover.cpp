#include "Remover.h"

Remover::Remover(int id, char symbol, int price)
	: Item(id, symbol, price)
{
	sprite = "¢À";
	symbol = CHAR_REMOVER;
	tag = CHAR_REMOVER;
}

Remover* Remover::create()
{
	Remover* newItem = new Remover(id, symbol, price);
	newItem->isActive = true;
	return newItem;
}

void Remover::update()
{
	if (isActive == true)
	{
		removeItems();
		isActive = false;
	}
}

void Remover::draw()
{

}

void Remover::start()
{

}

void Remover::removeItems()
{
	list<GameObject*>::iterator iter;

	for (iter = activeGameObjectList->begin(); iter != activeGameObjectList->end(); iter++)
	{
		if ((*iter)->tag == CHAR_ITEM && ((Item*)*iter)->canvasColPos == canvasColPos)
		{
			(*iter)->isActive = false;
		}
	}
}


