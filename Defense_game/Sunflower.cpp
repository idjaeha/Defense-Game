#include "Sunflower.h"

Sunflower::Sunflower(int id, char symbol, int price)
	: Item(id, symbol, price)
{
	symbol = CHAR_SUNFLOWER;
	tag = CHAR_ITEM;
	sprite = "��";
}

Sunflower* Sunflower::create()
{
	Sunflower* newItem = new Sunflower(id,  symbol, price);
	newItem->energyCount = createRandomNumber() % 41 + 10;
	newItem->isActive = true;
	newItem->life = 300;
	return newItem;
}

void Sunflower::start() {

}

void Sunflower::update()
{
	if (tag == CHAR_ITEM) {
		if (isActive == true) {
			if (energyCount <= 0) {
				createEnergy();
				energyCount = createRandomNumber() % 41 + 10;
			}

			energyCount -= 1;
			life -= 1;

			if (life <= 0) { // life�� 0 ���� �۾����� false�� �����Ѵ�.
				canvas[0][canvasColPos] = CHAR_BLANK;
				canvas[1][canvasColPos] = CHAR_BLANK;
				isActive = false;
			}
		}
	}
}

void Sunflower::createEnergy() {
	int availableIdxList[7] = { 0 };
	int tempCount = 0;
	int col;
	int idx;
	for (idx = 0; idx < 7; idx++) { // �عٶ�� ��ó���� �� ���� ã�´�.
		col = idx + canvasColPos - 3;
		if (0 <= col && col < CANVAS_SIZE_COL &&
			canvas[CANVAS_SIZE_ROW - 1][col] != CHAR_ENERGY) {
			availableIdxList[tempCount] = col;
			tempCount++;
		}
	}

	if (tempCount != 0) { // �� �� �߿� �� ���� ���� �������� �����Ѵ�.
		idx = availableIdxList[createRandomNumber() % tempCount];
		Energy* newEG = new Energy(idx, true, canvas);
		activeGameObjectList->push_back(newEG);
	}
}

void Sunflower::draw() {
	if (tag == CHAR_ITEM) {
		if (isActive) {
			canvas[0][canvasColPos] = symbol;
			canvas[1][canvasColPos] = symbol;
		}
	}
}