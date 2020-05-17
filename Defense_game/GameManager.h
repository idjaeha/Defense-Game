#pragma once
#include "GameObject.h"
#include "Cursor.h"
#include "UICursor.h"
#include "CanvasCursor.h"
#include "Item.h"
#include "Sunflower.h"
#include "Potato.h"
#include "Shield.h"
#include "Shooter.h"
#include "Remover.h"
#include "Shop.h"
#include "Spawner.h"
#include "Zombie.h"

class GameManager : public GameObject
{
public:
	bool isReady;
	char** map;
	char** canvas;
	
	int hp;				// 현재 체력
	int key;			// 키보드 입력 값
	int subkey;			// 키보드 보조 입력 값
	int energy;			// 현재 가지고 있는 에너지 값
	int gameOverCount;	// 게임의 남은 시간

	UICursor* uiCursor;
	CanvasCursor* canvasCursor;
	Cursor* cursors[CURSOR_NUM];
	Shop* shop;
	Spawner* spawner;
	
	list<GameObject*> activeGameObjectList;

	GameManager();
	void start();
	void InitGame();
	void putItem();
	void clearCanvas();
	void eatEnergy();
	void InputKey();
	void startGame();
	void drawCanvas();
	void renderUI();
	void renderMap();
	void renderEnergy();
	void renderHp();
	void renderPlayTime();
	void renderCanvas();
	void render();
	void update();
	void checkGameOver();
	void updateGameObjects();
	void drawGameObjects();
	void draw();
	void deleteObjects();
};

