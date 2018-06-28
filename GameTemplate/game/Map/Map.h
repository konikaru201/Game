/*!
*@brief	マップクラス
*/
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
#include "GalaxyBox.h"
#include "Earth.h"
#include "StageMarker.h"
#include "StageMarker2.h"
#include "StageMarker3.h"
#include "Needle.h"
#include "Needle2.h"
#include "Needle3.h"

//マップの配置情報
struct SMapInfo {
	const char* modelName;		//モデルデータ
	D3DXVECTOR3 position;		//座標
	D3DXQUATERNION rotation;	//回転
};

class Map : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	Map();
	/*!
	*@brief	デストラクタ
	*/
	~Map();
	/*!
	*@brief	更新する前に一度だけ呼ばれる関数
	*/
	bool Start();
	/*!
	*@brief	更新
	*/
	void Update();
	/*!
	*@brief	マップの生成
	*@param[in] mapLocInfo	マップの配置情報
	*@param[in] numObject	マップのオブジェクト数
	*@param[in] stageNumber	ステージ番号
	*/
	void Create(SMapInfo* mapLocInfo, int numObject);
	/*!
	*@brief	描画
	*/
	void Render();
	/*!
	*@brief	一番近い移動床１のワールド行列を計算
	*@param[in]		pos		比較するオブジェクトの座標
	*@return 一番近い移動床１のワールド行列
	*/
	const D3DXMATRIX& GetMoveFloorWorldMatrix(const D3DXVECTOR3& pos);
	/*!
	*@brief	一番近い移動床２のワールド行列を計算
	*@param[in]		pos		比較するオブジェクトの座標
	*@return 一番近い移動床２のワールド行列
	*/
	const D3DXMATRIX& GetMoveFloor2WorldMatrix(const D3DXVECTOR3& pos);
	/*!
	*@brief	移動床１のリストを取得
	*@return 移動床１のリスト
	*/
	std::list<MoveFloor*> GetMoveFloorList() const
	{
		return m_moveFloorList;
	}
	/*!
	*@brief	移動床２のリストを取得
	*@return 移動床２のリスト
	*/
	std::list<MoveFloor2*> GetMoveFloor2List() const
	{
		return m_moveFloor2List;
	}
	/*!
	*@brief	一番近い移動床１の座標を計算
	*@param[in]		pos		比較するオブジェクトの座標
	*@return 一番近い移動床１の座標
	*/
	const D3DXVECTOR3& GetMoveFloorPosition(const D3DXVECTOR3& pos);
	/*!
	*@brief	一番近い移動床１の座標を計算
	*@param[in]		pos		比較するオブジェクトの座標
	*@return 一番近い移動床１の座標
	*/
	const D3DXVECTOR3& GetMoveFloor2Position(const D3DXVECTOR3& pos);
	/*
	*@brief	地球のインスタンスを取得
	*/
	Earth* GetEarthInstance() const
	{
		return m_earth;
	}
	/*
	*@brief	ステージマーカーのインスタンスを取得
	*/
	StageMarker* GetStageMarkerInstance() const
	{
		return m_stageMarker;
	}
	/*
	*@brief	ステージマーカー2のインスタンスを取得
	*/
	StageMarker2* GetStageMarker2Instance() const
	{
		return m_stageMarker2;
	}
	/*
	*@brief	ステージマーカー3のインスタンスを取得
	*/
	StageMarker3* GetStageMarker3Instance() const
	{
		return m_stageMarker3;
	}
private:
	std::list<MoveFloor*>	m_moveFloorList;	//移動床１のリスト
	std::list<MoveFloor2*>	m_moveFloor2List;	//移動床２のリスト
	D3DXMATRIX				moveFloorMatrix;	//移動床１のワールド行列
	D3DXMATRIX				moveFloor2Matrix;	//移動床２のワールド行列
	Earth*					m_earth;			//地球のインスタンス
	StageMarker*			m_stageMarker;		//ステージマーカーのインスタンス
	StageMarker2*			m_stageMarker2;
	StageMarker3*			m_stageMarker3;
};

extern Map* map;
