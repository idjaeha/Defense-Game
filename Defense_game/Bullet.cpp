#include "Bullet.h"

Bullet::Bullet()
{
	canvasColPos = 0;
	value = CHAR_BULLET;
	moveCount = 0;
	damage = 1;
}

void Bullet::start()
{
}

void Bullet::draw()
{
	if (isActive == true)
	{
		if (canvas[1][canvasColPos] == CHAR_BLANK) {
			canvas[1][canvasColPos] = value;
		}
	}
}

void Bullet::update()
{
	if (isActive == true) {
		checkCollision();
		move();
	}
}

void Bullet::move()
{
	moveCount--;
	if (moveCount <= 0) {
		moveCount = 1;
		canvasColPos++;
	}
}

void Bullet::checkCollision()
{
	// º®¿¡ ºÎµúÇûÀ» ¶§
	if (canvasColPos >= CANVAS_SIZE_COL - 1) {
		isActive = false;
	}

	// Àû°ú ºÎµúÇûÀ» ¶§
	list<GameObject*>::iterator iter;
	for (iter = activeGameObjectList->begin(); iter != activeGameObjectList->end(); iter++) {
		if ((*iter)->tag == CHAR_ZOMBIE && ((Zombie *)(*iter))->canvasColPos <= canvasColPos) {
			(((Zombie*)(*iter))->life) -= damage;
			isActive = false;
			break;
		}
	}
}