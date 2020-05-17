#include "Shooter.h"

Shooter::Shooter(int id, char symbol, int price)
	: Item(id, symbol, price)
{
	symbol = CHAR_SHOOTER;
	tag = CHAR_ITEM;
	shootCount = 0;
	sprite = "ㄷ";
}

Shooter* Shooter::create() {
	Shooter* newItem = new Shooter(id, symbol, price);
	newItem->isActive = true;
	newItem->life = 500;
	return newItem;
}

void Shooter::start() {

}

void Shooter::update()
{
	if (tag == CHAR_ITEM) {
		if (isActive == true) {
			life--;
			shootCount--;

			if (life <= 0) { // life가 0 보다 작아지면 false로 변경한다.
				canvas[0][canvasColPos] = CHAR_BLANK;
				canvas[1][canvasColPos] = CHAR_BLANK;
				isActive = false;
			}

			if (shootCount <= 0) {
				shootCount = 5;
				Bullet* newBullet = getBullet();
				if (newBullet != NULL) {
					activeBullets.push_back(newBullet);
				}
			}

			updateBullets();
			deleteBullets();
		}
	}
}

void Shooter::updateBullets() {
	list<Bullet*>::iterator iter;
	for (iter = activeBullets.begin(); iter != activeBullets.end(); iter++) {
		if ((*iter)->isActive == true) {
			(*iter)->update();
		}
	}
}

void Shooter::deleteBullets() 
{
	list<Bullet*>::iterator iter;
	for (iter = activeBullets.begin(); iter != activeBullets.end(); iter++) {
		if ((*iter)->isActive == false) {
			activeBullets.erase(iter);
			break;
		}
	}
}


void Shooter::drawBullets() {
	list<Bullet*>::iterator iter;
	for (iter = activeBullets.begin(); iter != activeBullets.end(); iter++) {
		if ((*iter)->isActive == true) {
			(*iter)->draw();
		}
	}
}

void Shooter::draw()
{
	if (tag == CHAR_ITEM) {
		if (isActive) {
			canvas[0][canvasColPos] = symbol;
			canvas[1][canvasColPos] = symbol;
			drawBullets();
		}
	}
}

Bullet* Shooter::getBullet() {
	Bullet* newBullet = NULL;
	for (int idx = 0; idx < BULLET_NUM; idx++) {
		if (bullets[idx].isActive == false) {
			newBullet = &bullets[idx];
			break;
		}
	}

	if (newBullet != NULL) {
		newBullet->isActive = true;
		newBullet->canvas = canvas;
		newBullet->canvasColPos = canvasColPos;
		newBullet->activeGameObjectList = activeGameObjectList;
	}

	return newBullet;
}
