#pragma once

#include "Cursor.h"
#include "Item.h"

class CanvasCursor : public Cursor
{
public:
	int canvasIdx;		// canvas 내의 idx
	Item *selectedItem;	// 현재 커서에 의해 선택된 아이템

	CanvasCursor(int idx);
	void erase();
	void render();
	void blinkCursor();
	void Move(int dist);
	void start();
	void draw();
	void update();
};

