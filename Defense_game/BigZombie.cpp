#include "BigZombie.h"

BigZombie::BigZombie(int idx, list<GameObject*>* activeGameObjectList, char** canvas, int* hp)
	:Zombie(activeGameObjectList, canvas, 5, 10, hp)
{
	canvasColPos = idx;
	isActive = true;
	life = 10;
	tag = CHAR_ZOMBIE;
	symbol = CHAR_ZOMBIE_BIG;
}

void BigZombie::start()
{
}

void BigZombie::update()
{
	if (tag == CHAR_ZOMBIE)
	{
		if (isActive == true)
		{
			if (life <= 0) {
				isActive = false;
				return;
			}

			attack();
			move();
		}
	}
}

void BigZombie::move()
{
	moveCount--;
	if (moveCount <= 0)
	{
		if (canvasColPos >= 0) {
			if (canvasColPos > 0 && canvas[1][canvasColPos - 1] == CHAR_SHIELD) // 벽에 만났을 시에,
			{

			}
			else
			{
				canvasColPos--;
				moveCount = rawMoveCount;
			}
		}
		else {
			(*hp)--;
			isActive = false;
			return;
		}
	}
}

void BigZombie::attack()
{
	attackCount--;
	if (attackCount <= 0)
	{
		if (canvasColPos > 0 && canvas[1][canvasColPos - 1] == CHAR_SHIELD) // 벽에 만났을 시에,
		{
			// 만난 벽을 찾는다.
			GameObject* target = searchShield();
			// 만난 벽의 life를 깍는다.
			if (target != NULL)
			{
				((Item*)target)->life--;
			}
		}
		attackCount = rawAttackCount;
	}
}