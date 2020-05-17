#include "UICursor.h"

UICursor::UICursor(int idx, Shop* shop)
	:Cursor(idx), shop(shop), selectedItem(NULL)
{
}

void UICursor::erase() //지정된 부분을 지워주는 함수
{
	switch (idx) {
	case 0:
		gotoxy(POSITION_FLOWER, 1, "    ");
		gotoxy(POSITION_FLOWER, 2, "    ");
		break;
	case 1:
		gotoxy(POSITION_SHOOTER, 1, "    ");
		gotoxy(POSITION_SHOOTER, 2, "    ");
		break;
	case 2:
		gotoxy(POSITION_BOMB, 1, "    ");
		gotoxy(POSITION_BOMB, 2, "    ");
		break;
	case 3:
		gotoxy(POSITION_SHIELD, 1, "    ");
		gotoxy(POSITION_SHIELD, 2, "    ");
		break;
	case 4:
		gotoxy(POSITION_REMOVER, 1, "    ");
		break;
	default:
		break;
	}
}
void UICursor::render() { //플레이 영역(canvas에 그림)
}

void UICursor::blinkCursor() {
	if (blinkFlag) { //보이면 
		erase(); //지워주고
	}
	else { //안보이면
		render(); //그려주고
	}
	blinkFlag = (blinkFlag + 1) % 2;
}

void UICursor::Move(int dist) {
	int nextIdx = idx;
	for (int num = 0; num < ITEM_NUM; num++) {
		nextIdx = (nextIdx + dist) % ITEM_NUM;
		nextIdx = nextIdx <= -1 ? nextIdx = ITEM_NUM - 1 : nextIdx;
		if (shop->isAvailable(nextIdx)) {
			break;
		}
	}
	idx = nextIdx;
}

void UICursor::start()
{
}

void UICursor::draw()
{
}

void UICursor::update()
{
}
