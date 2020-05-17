#include "Define.h"
#include "Cursor.h"


Cursor::Cursor(int idx)
	:idx(idx), blinkFlag(false)
{
}

void Cursor::blinkCursor() {
	if (blinkFlag) { //���̸� 
		erase(); //�����ְ�
	}
	else { //�Ⱥ��̸�
		render(); //�׷��ְ�
	}
	blinkFlag = (blinkFlag + 1) % 2;
}