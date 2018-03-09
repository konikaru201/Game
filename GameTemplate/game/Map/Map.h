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
#include "Enemy/StoneMonster.h"
#include "Floor.h"

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

	const D3DXMATRIX& MoveFloorWorldMatrix(const D3DXVECTOR3& pos);

	const D3DXMATRIX& MoveFloor2WorldMatrix(const D3DXVECTOR3& pos);

	std::list<MoveFloor*> GetMoveFloorList()
	{
		return m_moveFloorList;
	}

	std::list<MoveFloor2*> GetMoveFloor2List()
	{
		return m_moveFloor2List;
	}

	const D3DXVECTOR3& GetMoveFloorPosition(const D3DXVECTOR3& pos);

	const D3DXVECTOR3& GetMoveFloor2Position(const D3DXVECTOR3& pos);

	bool GetIsMoveFloor()
	{
		return m_isMoveFloor;
	}

	bool GetIsMoveFloor2()
	{
		return m_isMoveFloor2;
	}

private:
	std::list<MoveFloor*> m_moveFloorList;
	std::list<MoveFloor2*> m_moveFloor2List;
	D3DXMATRIX moveFloorMatrix;
	D3DXMATRIX moveFloor2Matrix;
	bool m_isMoveFloor = false;
	bool m_isMoveFloor2 = false;
};

extern Map* map;
