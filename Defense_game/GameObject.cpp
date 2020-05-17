#include "GameObject.h"

GameObject::GameObject() {
	pos[ROW] = 0;
	pos[COL] = 0;
	isActive = false;
	tag = NULL;
}