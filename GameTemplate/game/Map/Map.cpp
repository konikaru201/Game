#include "stdafx.h"
#include "Map.h"
#include "myEngine/GameObject/GameObjectManager.h"

Map::Map()
{
}

Map::~Map()
{
}

bool Map::Start()
{
	return true;
}

void Map::Create(SMapInfo* mapLocInfo, int numObject)
{
	//オブジェクトを一個ずつロードしていく
	for (int i = 0; i < numObject; i++) {
		if (strcmp("MoveFloor", mapLocInfo[i].modelName) == 0) {
			//インスタンスを動的に生成
			g_moveFloor = goMgr->NewGameObject<MoveFloor>();
			//座標と回転の情報を渡して初期化
			g_moveFloor->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
 		}
		else if (strcmp("MoveFloor2", mapLocInfo[i].modelName) == 0) {
			//インスタンスを動的に生成
			g_moveFloor2 = goMgr->NewGameObject<MoveFloor2>();
			//座標と回転の情報を渡して初期化
			g_moveFloor2->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("Coin", mapLocInfo[i].modelName) == 0)
		{
			//インスタンスを動的に生成
			Coin* coin = goMgr->NewGameObject<Coin>();
			//座標と回転の情報を渡して初期化
			coin->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("Killer", mapLocInfo[i].modelName) == 0)
		{
			//インスタンスを動的に生成
			Killer* killer = goMgr->NewGameObject<Killer>();
			//座標と回転の情報を渡して初期化
			killer->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("JumpBlock", mapLocInfo[i].modelName) == 0)
		{
			//インスタンスを動的に生成
			jumpBlock = goMgr->NewGameObject<JumpBlock>();
			//座標と回転の情報を渡して初期化
			jumpBlock->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("block", mapLocInfo[i].modelName) == 0) 
		{
			//インスタンスを動的に生成
			Block* block = goMgr->NewGameObject<Block>();
			//座標と回転の情報を渡して初期化
			block->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("Box", mapLocInfo[i].modelName) == 0) {
			//インスタンスを動的に生成
			Box* box = goMgr->NewGameObject<Box>();
			//座標と回転の情報を渡して初期化
			box->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else {
			//MapChipのインスタンスを動的に生成
			MapChip* mapChip = goMgr->NewGameObject<MapChip>();
			//マップチップの情報を渡して初期化
			mapChip->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
	}
}

void Map::Update()
{
}

void Map::Render()
{
}