#include "Shield.h"

Shield::Shield(int id, char symbol, int price)
	: Item(id, symbol, price)
{
	symbol = CHAR_SHIELD;
	sprite = "¡å";
	tag = CHAR_SHIELD;
}

Shield* Shield::create() {
	Shield* newItem = new Shield(id, symbol, price);
	newItem->isActive = true;
	newItem->life = 50;
	return newItem;
}

void Shield::update() 
{
	if (isActive == true) 
	{
		if (life <= 0) 
		{
			isActive = false;
		}
	}
}

void Shield::draw()
{
	if (isActive == true)
	{
		canvas[0][canvasColPos] = life <= 50 ? life : 50;
		canvas[1][canvasColPos] = symbol;
	}
	else
	{
		canvas[0][canvasColPos] = CHAR_BLANK;
		canvas[1][canvasColPos] = CHAR_BLANK;
	}
}

void Shield::start()
{
}
