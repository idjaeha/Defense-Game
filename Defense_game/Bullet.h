#pragma once
#include "GameObject.h"
#include "Zombie.h"

class Bullet : public GameObject
{
public:
	Bullet();
	int damage;
	int moveCount;
	int canvasColPos;
	char value;
	char** canvas;
	list<GameObject*>* activeGameObjectList;

	void start();
	void draw();
	void update();
	void move();
	void checkCollision();
};

