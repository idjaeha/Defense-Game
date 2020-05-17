#include "NormalZombie.h"

NormalZombie::NormalZombie(int idx, list<GameObject*>* activeGameObjectList, char** canvas, int *hp)
	:Zombie(activeGameObjectList, canvas, 10, 10, hp)
{
	canvasColPos = idx;
	isActive = true;
	life = 10;
	tag = CHAR_ZOMBIE;
	symbol = CHAR_ZOMBIE_NORMAL;
}

void NormalZombie::start()
{
}

void NormalZombie::update()
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

void NormalZombie::move()
{
	moveCount--;
	if (moveCount <= 0)
	{
		if (canvasColPos >= 0) {
			if (canvasColPos > 0 && canvas[1][canvasColPos - 1] == CHAR_SHIELD) // ���� ������ �ÿ�,
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

void NormalZombie::attack()
{
	attackCount--;
	if (attackCount <= 0)
	{
		if (canvasColPos > 0 && canvas[1][canvasColPos - 1] == CHAR_SHIELD) // ���� ������ �ÿ�,
		{
			// ���� ���� ã�´�.
			GameObject* target = searchShield();
			// ���� ���� life�� ��´�.
			if (target != NULL)
			{
				((Item*)target)->life--;
			}
		}
		attackCount = rawAttackCount;
	}
}
