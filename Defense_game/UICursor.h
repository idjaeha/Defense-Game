#pragma once
#include "Cursor.h"
#include "Shop.h"

class UICursor : public Cursor{
public:
	Item* selectedItem;	// ���� Ŀ���� ���� ���õ� ������
	Shop* shop;

	UICursor(int idx, Shop* shop);
	void erase();
	void render();
	void blinkCursor();
	void Move(int dist);
	void start();
	void draw();
	void update();
};

