#include "Energy.h"

Energy::Energy()
	: Item(-1, CHAR_ENERGY, 0)
{
	life = 200;
	symbol = CHAR_ENERGY;
	tag = CHAR_ITEM;
}

Energy::Energy(int idx, bool isActive, char** canvas)
	: Item(-1, CHAR_ENERGY, 0)
{
	this->isActive = isActive;
	this->canvas = canvas;
	this->canvasColPos = idx;
	life = 200;
	symbol = CHAR_ENERGY;
	tag = CHAR_ITEM;
	start();
}

void Energy::start() {
	canvas[CANVAS_SIZE_ROW - 1][canvasColPos] = symbol;
}

void Energy::draw() {
	if (tag == CHAR_ITEM) {
		if (isActive) {
			canvas[CANVAS_SIZE_ROW - 1][canvasColPos] = symbol;
		}
	}
}

void Energy::update()
{
	if (tag == CHAR_ITEM) {
		if (isActive == true) {
			life -= 1;
			if (canvas[CANVAS_SIZE_ROW - 1][canvasColPos] != symbol) {
				isActive = false;
			}

			if (life <= 0) { // life가 0 보다 작아지면 false로 변경한다.
				canvas[2][canvasColPos] = CHAR_BLANK;
				isActive = false;
			}
		}
	}
}

Energy* Energy::create() {
	return new Energy();
}