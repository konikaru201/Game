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
		if (strcmp("MoveFloor_1", mapLocInfo[i].modelName) == 0) {
			//インスタンスを動的に生成
			MoveFloor* moveFloor = goMgr->NewGameObject<MoveFloor>();
			//座標と回転の情報を渡して初期化
			moveFloor->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("MoveFloor_2", mapLocInfo[i].modelName) == 0) {
			//インスタンスを動的に生成
			MoveFloor2* moveFloor2 = goMgr->NewGameObject<MoveFloor2>();
			//座標と回転の情報を渡して初期化
			moveFloor2->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
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
		else if (strcmp("Spring", mapLocInfo[i].modelName) == 0)
		{
			//インスタンスを動的に生成
			Spring* spring = goMgr->NewGameObject<Spring>();
			//座標と回転の情報を渡して初期化
			spring->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("Block_1", mapLocInfo[i].modelName) == 0)
		{
			//インスタンスを動的に生成
			Block* block = goMgr->NewGameObject<Block>();
			//座標と回転の情報を渡して初期化
			block->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if(strcmp("Block_2", mapLocInfo[i].modelName) == 0)
		{
			//インスタンスを動的に生成
			Block2* block2 = goMgr->NewGameObject<Block2>();
			//座標と回転の情報を渡して初期化
			block2->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("Box", mapLocInfo[i].modelName) == 0) 
		{
			//インスタンスを動的に生成
			Box* box = goMgr->NewGameObject<Box>();
			//座標と回転の情報を渡して初期化
			box->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if(strcmp("skyBox", mapLocInfo[i].modelName) == 0)
		{
			//インスタンスを動的に生成
			SkyBox* skyBox = goMgr->NewGameObject<SkyBox>();
			//座標と回転の情報を渡して初期化
			skyBox->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("Star", mapLocInfo[i].modelName) == 0)
		{
			//インスタンスを動的に生成
			Star* star = goMgr->NewGameObject<Star>();
			//座標と回転の情報を渡して初期化
			star->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("Red_Dragon", mapLocInfo[i].modelName) == 0) {
			//インスタンスを動的に生成
			Red_Dragon* red_Dragon = goMgr->NewGameObject<Red_Dragon>();
			//座標と回転の情報を渡して初期化
			red_Dragon->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else 
		{
			//インスタンスを動的に生成
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