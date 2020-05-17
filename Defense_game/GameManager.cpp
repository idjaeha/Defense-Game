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

	//�ʰ� ĵ������ �����Ѵ�.
	map = new char*[MAP_SIZE_ROW];
	for (int row = 0; row < MAP_SIZE_ROW; row++) {
		map[row] = new char[MAP_SIZE_COL];
	}

	canvas = new char* [CANVAS_SIZE_ROW];
	for (int row = 0; row < CANVAS_SIZE_ROW; row++) {
		canvas[row] = new char[CANVAS_SIZE_COL];
	}

	// �ʰ� ĵ������ �����Ѵ�.
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

	// �Ǹ��� Item���� �����Ͽ� shop�� �߰��Ѵ�.
	// �ι�° ���ڸ� ���� �Ǹ��� Item�� ��Ÿ���� �����Ѵ�.
	// ������ ���ϸ� 0���� �ʱ�ȭ�ȴ�.
	shop->addItem(new Sunflower(0, CHAR_SUNFLOWER, 50), 10);
	shop->addItem(new Shooter(1, CHAR_SHOOTER, 100));
	shop->addItem(new Potato(2, CHAR_POTATO, 25));
	shop->addItem(new Shield(3, CHAR_SHIELD, 50));
	shop->addItem(new Remover(4, CHAR_REMOVER, 0));


	// Cursor�� �����Ѵ�.
	uiCursor = new UICursor(-1, shop);
	canvasCursor = new CanvasCursor(CANVAS_START_COL);
	cursors[0] = uiCursor;
	cursors[1] = canvasCursor;

	// ������ �ʱ�ȭ
	energy = 1000;
	hp = 5;
	isReady = true;
}

void GameManager::putItem()
{
	if (canvasCursor->selectedItem != NULL)	//�������� �� ���°�
	{
		if (canvas[1][canvasCursor->canvasIdx] == CHAR_BLANK || 
			canvasCursor->selectedItem->tag == CHAR_POTATO ||
			canvasCursor->selectedItem->tag == CHAR_REMOVER)
			//�������� ��ġ�� ������̰ų� �������� ���� ��ź�̸� ����
		{
			Item* tempItem = canvasCursor->selectedItem;
			Item* newItem = tempItem->create();
			newItem->activeGameObjectList = &activeGameObjectList;
			newItem->canvas = canvas;
			newItem->canvasColPos = canvasCursor->canvasIdx;
			activeGameObjectList.push_back(newItem);
			canvasCursor->selectedItem = NULL; // ��ġ�� �Ϸ�����Ƿ� �ٽ� ���õ� ������ �������� ����
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
		case KEY_ENTER: // ���� : ���õ� �������� ��ġ
			putItem();
			break;
		case ' ': // �����̽� : UIâ���� ������ ����
			if (canvasCursor->selectedItem == NULL) { //���õ� �������� ���� ��
				canvasCursor->selectedItem = shop->sell(uiCursor->idx); // ���Ÿ� �������� �ÿ��� �ش� �������� ��ȯ
																		// �������� �ÿ��� NULL�� ��ȯ�Ѵ�.
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

	gotoxy(POSITION_FLOWER, 1, "�ع�");
	gotoxy(POSITION_FLOWER, 2, "���");

	gotoxy(POSITION_SHOOTER, 1, "��");
	gotoxy(POSITION_SHOOTER, 2, "����");

	gotoxy(POSITION_BOMB, 1, "����");
	gotoxy(POSITION_BOMB, 2, "��ź");

	gotoxy(POSITION_SHIELD, 1, "ȣ��");
	gotoxy(POSITION_SHIELD, 2, "����");

	gotoxy(POSITION_REMOVER, 1, "��");
}

void GameManager::renderMap() {
	int row, col;
	for (row = 0; row < MAP_SIZE_ROW; row++) {
		for (col = 0; col < MAP_SIZE_COL; col++) {
			char temp = map[row][col];
			if (temp == CHAR_BLANK) { //�����
				gotoxy(col * 2, row, "  ");
			}
			else if (temp == CHAR_WALL) { //��
				gotoxy(col * 2, row, "��");
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
	// Map���� canvas�� �ش��ϴ� �κи� ���� ����մϴ�.
	int canvasRow, canvasCol;
	int row, col;
	for (canvasRow = 0; canvasRow < CANVAS_SIZE_ROW; canvasRow++) {
		for (canvasCol = 0; canvasCol < CANVAS_SIZE_COL; canvasCol++) {
			char temp = canvas[canvasRow][canvasCol];
			row = canvasRow + CANVAS_START_ROW;
			col = canvasCol + CANVAS_START_COL;
			if (temp == CHAR_BLANK) { //�����
				gotoxy(col * 2, row, "  ");
			}
			else if (temp == CHAR_SUNFLOWER) { //�عٶ��
				gotoxy(col * 2, row, "��");
			}
			else if (temp == CHAR_SHOOTER) { //�ὴ�� 
				gotoxy(col * 2, row, "��");
			}
			else if (temp == CHAR_POTATO) { //������ź 
				gotoxy(col * 2, row, "��");
			}
			else if (temp == CHAR_SHIELD) { //ȣ�ι��� 
				gotoxy(col * 2, row, "��");
			}
			else if (temp == CHAR_REMOVER) { //�� 
				gotoxy(col * 2, row, "��");
			}
			else if (temp == CHAR_ENERGY) { //������
				gotoxy(col * 2, row, "EG");
			}
			else if (temp == CHAR_ZOMBIE_NORMAL) { // �⺻ ����
				gotoxy(col * 2, row, "NZ");
			}
			else if (temp == CHAR_ZOMBIE_BIG) { // �����
				gotoxy(col * 2, row, "CZ");
			}
			else if (temp == CHAR_ZOMBIE) { // �����
				gotoxy(col * 2, row, " Z");
			}
			else if (temp == CHAR_BULLET) { // �Ѿ�
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

void GameManager::render() { //�ܼ�â�� ����ϴ� �Լ�
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
	// Ȱ��ȭ�� �����۵��� ������Ʈ�Ѵ�.
	list<GameObject*>::iterator iter;
	for (iter = activeGameObjectList.begin(); iter != activeGameObjectList.end(); iter++) {
		(*iter)->update();
	}
}

void GameManager::drawGameObjects() {
	// Ȱ��ȭ�� �����۵��� �迭�� �׸���.
	list<GameObject*>::iterator iter;
	for (iter = activeGameObjectList.begin(); iter != activeGameObjectList.end(); iter++) {
		(*iter)->draw();
	}
}

void GameManager::draw()
{ 
	// �� �迭�� �׸��� ����
	clearCanvas();
	drawGameObjects();
	drawCanvas();
}

void GameManager::deleteObjects() {
	// Ȱ��ȭ�� ������ Object�� �����Ѵ�.
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
	// ������ ���� �غ�Ǿ����� �ʴٸ� �غ��Ѵ�.
	if (isReady == false) {
		InitGame();
	}

	renderMap(); // �⺻ ���� ���� �׷��ش�.
	while (isReady) { //���ӷ���
		InputKey();
		update();
		draw();
		render();
		Sleep(100);
	}//while
}
