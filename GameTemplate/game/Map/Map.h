#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "MapChip.h"
#include "MoveFloor.h"
#include "MoveFloor2.h"
#include "Coin.h"
#include "Enemy/Killer.h"
#include "Spring.h"
#include "Block.h"
#include "Block2.h"
#include "Box.h"
#include "SkyBox.h"
#include "Star.h"
#include "Enemy/Red_Dragon.h"

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

	//ジャンプブロックのインスタンスを取得
	Spring* GetSpring()
	{
		return spring;
	}
private:
	Spring* spring;		//ジャンプブロックのインスタンス
};

