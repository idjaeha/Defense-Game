#include "CanvasCursor.h"

CanvasCursor::CanvasCursor(int idx)
	:Cursor(idx), selectedItem(NULL)
{
	canvasIdx = 0;
}

void CanvasCursor::erase() //지정된 부분을 지워주는 함수
{
	if (CANVAS_START_COL <= idx && idx < CANVAS_START_COL + 28) { //게임플레이 화면의 커서에서 지워주기
		int mapPos = idx * 2; //실제값은 두배해줘야함
		gotoxy(mapPos, 1, "  ");
		gotoxy(mapPos, 2, "  ");
		gotoxy(mapPos, 3, "  ");
		gotoxy(mapPos, 4, "  ");
		gotoxy(mapPos, 5, "  ");
	}
}
void CanvasCursor::render() { //플레이 영역(canvas에 그림)
	int renderIdx = idx * 2;

	if (selectedItem != NULL) {
		gotoxy(renderIdx, 1, selectedItem->sprite);
		gotoxy(renderIdx, 2, selectedItem->sprite);
	}

}

void CanvasCursor::blinkCursor() {
	if (blinkFlag) { //보이면 
		erase(); //지워주고
	}
	else { //안보이면
		render(); //그려주고
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
