#pragma once
#include "Cursor.h"
#include "Shop.h"

class UICursor : public Cursor{
public:
	Item* selectedItem;	// 현재 커서에 의해 선택된 아이템
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

