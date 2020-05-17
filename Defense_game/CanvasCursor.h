#pragma once

#include "Cursor.h"
#include "Item.h"

class CanvasCursor : public Cursor
{
public:
	int canvasIdx;		// canvas ���� idx
	Item *selectedItem;	// ���� Ŀ���� ���� ���õ� ������

	CanvasCursor(int idx);
	void erase();
	void render();
	void blinkCursor();
	void Move(int dist);
	void start();
	void draw();
	void update();
};

