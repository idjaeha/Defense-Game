#include "GameManager.h"

GameManager::GameManager() {
	start();
}

void GameManager::start() {
	InitGame();
}

void GameManager::InitGame() {
	int row, col;
	char rawMap[MAP_SIZE_ROW][MAP_SIZE_COL] = {
			{"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"},
			{"WBBBWBBWBBWBBWBBWBBWBBBBBBBBBBBBBBBBBBBBBBBBBBBBW"},
			{"WBBBWBBWBBWBBWBBWBBWBBBBBBBBBBBBBBBBBBBBBBBBBBBBW"},
			{"WBBBWBBWBBWBBWBBWBBWBBBBBBBBBBBBBBBBBBBBBBBBBBBBW"},
			{"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"}
	};

	char rawCanvas[CANVAS_SIZE_ROW][CANVAS_SIZE_COL] = {
		{"BBBBBBBBBBBBBBBBBBBBBBBBBBBB"},
		{"BBBBBBBBBBBBBBBBBBBBBBBBBBBB"},
		{"BBBBBBBBBBBBBBBBBBBBBBBBBBBB"}
	};

	//맵과 캔버스를 생성한다.
	map = new char*[MAP_SIZE_ROW];
	for (int row = 0; row < MAP_SIZE_ROW; row++) {
		map[row] = new char[MAP_SIZE_COL];
	}

	canvas = new char* [CANVAS_SIZE_ROW];
	for (int row = 0; row < CANVAS_SIZE_ROW; row++) {
		canvas[row] = new char[CANVAS_SIZE_COL];
	}

	// 맵과 캔버스를 복사한다.
	for (row = 0; row < MAP_SIZE_ROW; row++) {
		for (col = 0; col < MAP_SIZE_COL; col++) {
			map[row][col] = rawMap[row][col];
		}
	}

	for (row = 0; row < CANVAS_SIZE_ROW; row++) {
		for (col = 0; col < CANVAS_SIZE_COL; col++) {
			canvas[row][col] = rawCanvas[row][col];
		}
	}

	shop = new Shop(&energy);
	spawner = new Spawner(canvas, &activeGameObjectList, &hp);

	// 판매할 Item들을 생성하여 shop에 추가한다.
	// 두번째 인자를 통해 판매할 Item의 쿨타임을 설정한다.
	// 설정을 안하면 0으로 초기화된다.
	shop->addItem(new Sunflower(0, CHAR_SUNFLOWER, 50), 10);
	shop->addItem(new Shooter(1, CHAR_SHOOTER, 100));
	shop->addItem(new Potato(2, CHAR_POTATO, 25));
	shop->addItem(new Shield(3, CHAR_SHIELD, 50));
	shop->addItem(new Remover(4, CHAR_REMOVER, 0));


	// Cursor를 생성한다.
	uiCursor = new UICursor(-1, shop);
	canvasCursor = new CanvasCursor(CANVAS_START_COL);
	cursors[0] = uiCursor;
	cursors[1] = canvasCursor;

	// 에너지 초기화
	energy = 1000;
	hp = 5;
	isReady = true;
}

void GameManager::putItem()
{
	if (canvasCursor->selectedItem != NULL)	//아이템을 고른 상태고
	{
		if (canvas[1][canvasCursor->canvasIdx] == CHAR_BLANK || 
			canvasCursor->selectedItem->tag == CHAR_POTATO ||
			canvasCursor->selectedItem->tag == CHAR_REMOVER)
			//놓으려는 위치가 빈공간이거나 아이템이 감자 폭탄이면 실행
		{
			Item* tempItem = canvasCursor->selectedItem;
			Item* newItem = tempItem->create();
			newItem->activeGameObjectList = &activeGameObjectList;
			newItem->canvas = canvas;
			newItem->canvasColPos = canvasCursor->canvasIdx;
			activeGameObjectList.push_back(newItem);
			canvasCursor->selectedItem = NULL; // 설치가 완료됬으므로 다시 선택된 아이템 없음으로 설정
		}
	}
}

void GameManager::clearCanvas()
{
	for (int col = 0; col < CANVAS_SIZE_COL; col++)
	{
		char flag = canvas[1][col];
		switch (flag) {
		case CHAR_ZOMBIE_NORMAL:
		case CHAR_ZOMBIE_BIG:
		case CHAR_ZOMBIE:
			canvas[0][col] = CHAR_BLANK;
			canvas[1][col] = CHAR_BLANK;
			break;
		case CHAR_BULLET:
			canvas[1][col] = CHAR_BLANK;
			break;
		default:
			break;
		}
	}
}

void GameManager::eatEnergy()
{
	if (canvas[CANVAS_SIZE_ROW - 1][canvasCursor->canvasIdx] == CHAR_ENERGY) {
		canvas[CANVAS_SIZE_ROW - 1][canvasCursor->canvasIdx] = CHAR_BLANK;
		energy += 20;
	}
}

void GameManager::InputKey()
{
	if (_kbhit()) {
		key = _getch();
		subkey = NULL;

		switch (key) {
		case 'a':
			uiCursor->Move(-1);
			break;
		case 'd':
			uiCursor->Move(1);
			break;
		case 's':
			eatEnergy();
			break;
		case KEY_ENTER: // 엔터 : 선택된 아이템을 배치
			putItem();
			break;
		case ' ': // 스페이스 : UI창에서 아이템 선택
			if (canvasCursor->selectedItem == NULL) { //선택된 아이템이 없을 때
				canvasCursor->selectedItem = shop->sell(uiCursor->idx); // 구매를 성공했을 시에는 해당 아이템을 반환
																		// 실패했을 시에는 NULL을 반환한다.
			}
			break;
		case KEY_ARROW_1:
			subkey = _getch();
			if (subkey == KEY_ARROW_RIGHT) {
				canvasCursor->Move(1);
			}
			else if (subkey == KEY_ARROW_LEFT) {
				canvasCursor->Move(-1);
			}
			break;
		case KEY_ESC: // ESC
			isReady = false;
			return;
			break;
		default:
			break;
		}
	}
}

void GameManager::drawCanvas()
{
	for (int row = 0; row < CANVAS_SIZE_ROW; row++) {
		for (int col = 0; col < CANVAS_SIZE_COL - 1; col++) {
			map[CANVAS_START_ROW + row][CANVAS_START_COL + col] = canvas[row][col];
		}
	}
}

void GameManager::renderUI() {
	gotoxy(POSITION_ENERGE, 1, "EG ");

	gotoxy(POSITION_FLOWER, 1, "해바");
	gotoxy(POSITION_FLOWER, 2, "라기");

	gotoxy(POSITION_SHOOTER, 1, "콩");
	gotoxy(POSITION_SHOOTER, 2, "슈터");

	gotoxy(POSITION_BOMB, 1, "감자");
	gotoxy(POSITION_BOMB, 2, "폭탄");

	gotoxy(POSITION_SHIELD, 1, "호두");
	gotoxy(POSITION_SHIELD, 2, "방패");

	gotoxy(POSITION_REMOVER, 1, "삽");
}

void GameManager::renderMap() {
	int row, col;
	for (row = 0; row < MAP_SIZE_ROW; row++) {
		for (col = 0; col < MAP_SIZE_COL; col++) {
			char temp = map[row][col];
			if (temp == CHAR_BLANK) { //빈공간
				gotoxy(col * 2, row, "  ");
			}
			else if (temp == CHAR_WALL) { //벽
				gotoxy(col * 2, row, "■");
			}
		}
		printf("\n");
	}
}

void GameManager::renderEnergy() {
	gotoxy(4, 1, energy);
}

void GameManager::renderHp() 
{
	gotoxy(2, 2);
	printf("HP %3d", hp);
}

void GameManager::renderCanvas() {
	// Map에서 canvas에 해당하는 부분만 따로 출력합니다.
	int canvasRow, canvasCol;
	int row, col;
	for (canvasRow = 0; canvasRow < CANVAS_SIZE_ROW; canvasRow++) {
		for (canvasCol = 0; canvasCol < CANVAS_SIZE_COL; canvasCol++) {
			char temp = canvas[canvasRow][canvasCol];
			row = canvasRow + CANVAS_START_ROW;
			col = canvasCol + CANVAS_START_COL;
			if (temp == CHAR_BLANK) { //빈공간
				gotoxy(col * 2, row, "  ");
			}
			else if (temp == CHAR_SUNFLOWER) { //해바라기
				gotoxy(col * 2, row, "◎");
			}
			else if (temp == CHAR_SHOOTER) { //콩슈터 
				gotoxy(col * 2, row, "ㄷ");
			}
			else if (temp == CHAR_POTATO) { //감자폭탄 
				gotoxy(col * 2, row, "◆");
			}
			else if (temp == CHAR_SHIELD) { //호두방패 
				gotoxy(col * 2, row, "▼");
			}
			else if (temp == CHAR_REMOVER) { //삽 
				gotoxy(col * 2, row, "♣");
			}
			else if (temp == CHAR_ENERGY) { //에너지
				gotoxy(col * 2, row, "EG");
			}
			else if (temp == CHAR_ZOMBIE_NORMAL) { // 기본 좀비
				gotoxy(col * 2, row, "NZ");
			}
			else if (temp == CHAR_ZOMBIE_BIG) { // 콘헤드
				gotoxy(col * 2, row, "CZ");
			}
			else if (temp == CHAR_ZOMBIE) { // 좀비들
				gotoxy(col * 2, row, " Z");
			}
			else if (temp == CHAR_BULLET) { // 총알
				gotoxy(col * 2, row, " -");
			}
			else if (0 < temp && temp <= 50) {
				gotoxy(col * 2, row);
				printf("%2d", temp);
			}
		}
		printf("\n");
	}
}

void GameManager::render() { //콘솔창에 출력하는 함수
	renderCanvas();
	renderUI();
	renderEnergy();
	renderHp();
	cursors[0]->blinkCursor();
	cursors[1]->blinkCursor();
}

void GameManager::update() {
	deleteObjects();
	shop->update();
	spawner->update();
	updateGameObjects();
	checkGameOver();
}

void GameManager::checkGameOver()
{
	if (hp <= 0) {
		isReady = false;
	}
}

void GameManager::updateGameObjects() {
	// 활성화된 아이템들을 업데이트한다.
	list<GameObject*>::iterator iter;
	for (iter = activeGameObjectList.begin(); iter != activeGameObjectList.end(); iter++) {
		(*iter)->update();
	}
}

void GameManager::drawGameObjects() {
	// 활성화된 아이템들을 배열에 그린다.
	list<GameObject*>::iterator iter;
	for (iter = activeGameObjectList.begin(); iter != activeGameObjectList.end(); iter++) {
		(*iter)->draw();
	}
}

void GameManager::draw()
{ 
	// 맵 배열에 그리는 행위
	clearCanvas();
	drawGameObjects();
	drawCanvas();
}

void GameManager::deleteObjects() {
	// 활성화가 중지된 Object를 해제한다.
	list<GameObject*>::iterator iterItem;
	for (iterItem = activeGameObjectList.begin(); iterItem != activeGameObjectList.end(); iterItem++) {
		if ((*iterItem)->isActive == false) {
			delete(*iterItem);
			activeGameObjectList.erase(iterItem);
			return;
		}
	}
}

void GameManager::startGame() {
	// 게임이 만약 준비되어있지 않다면 준비한다.
	if (isReady == false) {
		InitGame();
	}

	renderMap(); // 기본 맵을 먼저 그려준다.
	while (isReady) { //게임루프
		InputKey();
		update();
		draw();
		render();
		Sleep(100);
	}//while
}
