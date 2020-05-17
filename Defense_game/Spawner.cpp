#include "Spawner.h"

Spawner::Spawner(char** canvas, list<GameObject*>* activeGameObjectList, int* hp)
	:activeGameObjectList(activeGameObjectList), canvas(canvas), hp(hp)
{
	spawnNormalCount = 0;
	spawnBigCount = 0;
	startCount = 10;
}

void Spawner::start() {

}

void Spawner::update() {
	if (isActive == false) {
		startCount--;
		isActive = startCount <= 0 ? true : false;
	}
	else {
		spawnNormalCount--;
		spawnBigCount--;
		if (spawnNormalCount <= 0) {
			srand((unsigned int)time(0));
			spawnNormalCount = (rand() % 5) * 10 + 100;
			spawn(ZOMBIE_NORMAL);
		}
		if (spawnBigCount <= 0) {
			spawnBigCount = (rand() % 5) * 10 + 100;
			spawn(ZOMBIE_BIG);
		}
	}
}

void Spawner::draw() {

}

void Spawner::spawn(int id) {
	Zombie* newZombie = NULL;
	if (id == ZOMBIE_NORMAL) {
		newZombie = new NormalZombie(CANVAS_SIZE_COL - 1, activeGameObjectList, canvas, hp);
	}
	else if (id == ZOMBIE_BIG) {
		newZombie = new BigZombie(CANVAS_SIZE_COL - 1, activeGameObjectList, canvas, hp);
	}


	if (newZombie != NULL) {
		activeGameObjectList->push_back(newZombie);
	}
}