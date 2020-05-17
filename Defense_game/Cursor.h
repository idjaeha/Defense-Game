#pragma once
#include "Define.h"
#include "GameObject.h"

class Cursor : public GameObject{
public:
	int idx;			// ���� Ŀ���� idx
	bool blinkFlag;
	
	Cursor(int pos);
	virtual void erase() = 0;
	virtual void render() = 0;
	void blinkCursor();
	virtual void  Move(int dist) = 0;
};