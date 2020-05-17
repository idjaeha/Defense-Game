#include "Zombie.h"

Zombie::Zombie(list<GameObject*>* activeGameObjectList, char** canvas, int rawMoveCount, int rawAttackCount , int* hp)
	:rawMoveCount(rawMoveCount), rawAttackCount(rawAttackCount),
	moveCount(rawMoveCount), attackCount(rawAttackCount),
	canvas(canvas), activeGameObjectList(activeGameObjectList),
	hp(hp)
{
	tag = CHAR_ZOMBIE;
}

void Zombie::draw()
{
	char flag = canvas[1][canvasColPos];
	switch (flag) {
	case CHAR_BULLET:
	case CHAR_BLANK:
		canvas[1][canvasColPos] = symbol;
		canvas[0][canvasColPos] = 1;
		break;
	case CHAR_ZOMBIE_BIG:
	case CHAR_ZOMBIE_NORMAL:
	case CHAR_ZOMBIE:
		if (flag == symbol)
		{
			if (canvas[0][canvasColPos] < 50) {
				canvas[0][canvasColPos]++;
			}
		}
		else
		{
			canvas[1][canvasColPos] = CHAR_ZOMBIE;
			if (canvas[0][canvasColPos] < 50) {
				canvas[0][canvasColPos]++;
			}
		}
		break;
	default:
		break;
	}
}

GameObject* Zombie::searchShield()
{
	list<GameObject*>::iterator iter;
	for (iter = activeGameObjectList->begin(); iter != activeGameObjectList->end(); iter++)
	{
		if ((*iter)->tag == CHAR_SHIELD)
		{
			return (*iter);
		}
	}

	return NULL;
}