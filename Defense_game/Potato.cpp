#include "Potato.h"

Potato::Potato(int id, char symbol, int price)
	: Item(id, symbol, price)
{
	symbol = CHAR_POTATO;
	tag = CHAR_POTATO;
	sprite = "¡ß";
}

Potato* Potato::create() {
	Potato* newItem = new Potato(id, symbol, price);
	newItem->isActive = true;
	return newItem;
}

void Potato::update() {
	if (isActive == true)
	{
		killZombies();
		isActive = false;
	}
}

void Potato::draw()
{
}

void Potato::start()
{
}

void Potato::killZombies() {
	list<GameObject*>::iterator iter;
	for (iter = activeGameObjectList->begin(); iter != activeGameObjectList->end(); iter++)
	{

		if ((*iter)->tag == CHAR_ZOMBIE && ((Zombie*)*iter)->canvasColPos == canvasColPos)
		{
			((Zombie*)*iter)->isActive = false;
		}
	}
}
