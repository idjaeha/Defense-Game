#include "Define.h"
#include "Cursor.h"


Cursor::Cursor(int idx)
	:idx(idx), blinkFlag(false)
{
}

void Cursor::blinkCursor() {
	if (blinkFlag) { //보이면 
		erase(); //지워주고
	}
	else { //안보이면
		render(); //그려주고
	}
	blinkFlag = (blinkFlag + 1) % 2;
}