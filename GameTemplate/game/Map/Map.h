#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "MapChip.h"
#include "MoveFloor.h"
#include "MoveFloor2.h"
#include "Coin.h"
#include "Enemy/Killer.h"
#include "JumpBlock.h"
#include "Block.h"
#include "Box.h"
#include "Test.h"

//マップの配置情報
struct SMapInfo {
	const char* modelName;		//モデルデータ
	D3DXVECTOR3 position;		//座標
	D3DXQUATERNION rotation;	//回転
};

class Map : public GameObject
{
public:
	//コンストラクタ
	Map();

	//デストラクタ
	~Map();

	//初期化
	bool Start();

	//更新
	void Update();

	//マップの生成
	//mapLocInfo	マップの配置情報
	//numObject		マップのオブジェクト数
	void Create(SMapInfo* mapLocInfo, int numObject);

	//描画
	void Render();

	////移動床(横)のインスタンスを取得
	//MoveFloor* GetMoveFloor()
	//{
	//	return moveFloor;
	//}

	////移動床(縦)のインスタンスを取得
	//MoveFloor2* GetMoveFloor2()
	//{
	//	return moveFloor2;
	//}

	//ジャンプブロックのインスタンスを取得
	JumpBlock* GetJumpBlock()
	{
		return jumpBlock;
	}
private:
	//MoveFloor* moveFloor;		//移動床(横)のインスタンス
	//MoveFloor2* moveFloor2;		//移動床(縦)のインスタンス
	JumpBlock* jumpBlock;		//ジャンプブロックのインスタンス
};

