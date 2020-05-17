#include "UICursor.h"

UICursor::UICursor(int idx, Shop* shop)
	:Cursor(idx), shop(shop), selectedItem(NULL)
{
}

void UICursor::erase() //������ �κ��� �����ִ� �Լ�
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
void UICursor::render() { //�÷��� ����(canvas�� �׸�)
}

void UICursor::blinkCursor() {
	if (blinkFlag) { //���̸� 
		erase(); //�����ְ�
	}
	else { //�Ⱥ��̸�
		render(); //�׷��ְ�
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
