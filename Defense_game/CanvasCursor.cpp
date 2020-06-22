#include "CanvasCursor.h"

CanvasCursor::CanvasCursor(int idx)
	:Cursor(idx), selectedItem(NULL)
{
	canvasIdx = 0;
}

void CanvasCursor::erase() //������ �κ��� �����ִ� �Լ�
{
	if (CANVAS_START_COL <= idx && idx < CANVAS_START_COL + 28) { //�����÷��� ȭ���� Ŀ������ �����ֱ�
		int mapPos = idx * 2; //�������� �ι��������
		gotoxy(mapPos, 1, "  ");
		gotoxy(mapPos, 2, "  ");
		gotoxy(mapPos, 3, "  ");
		gotoxy(mapPos, 4, "  ");
		gotoxy(mapPos, 5, "  ");
	}
}
void CanvasCursor::render() { //�÷��� ����(canvas�� �׸�)
	int renderIdx = idx * 2;

	if (selectedItem != NULL) {
		gotoxy(renderIdx, 1, selectedItem->sprite);
		gotoxy(renderIdx, 2, selectedItem->sprite);
	}

}

void CanvasCursor::blinkCursor() {
	if (blinkFlag) { //���̸� 
		erase(); //�����ְ�
	}
	else { //�Ⱥ��̸�
		render(); //�׷��ְ�
	}
	blinkFlag = (blinkFlag + 1) % 2;
}

void CanvasCursor::Move(int dist) {
	int nextIdx = canvasIdx + dist;
	if (0 <= nextIdx && nextIdx < CANVAS_SIZE_COL - 1) {
		canvasIdx += dist;
		idx = canvasIdx + CANVAS_START_COL;
	}
}

void CanvasCursor::start()
{
}

void CanvasCursor::draw()
{
}

void CanvasCursor::update()
{
}
