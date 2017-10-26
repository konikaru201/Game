#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"

class MoveFloor2 : public GameObject
{
public:
	//コンストラクタ
	MoveFloor2();

	//デストラクタ
	~MoveFloor2();

	//初期化
	//pos	座標
	//rot	回転
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//更新
	void Update();
	void PreUpdate();
	//描画
	void Render();

	//移動
	void Move();

	//移動速度を取得
	D3DXVECTOR3& GetMoveSpeed()
	{
		return moveSpeed;
	}

	//移動フラグの取得
	bool GetmoveFlg()
	{
		return moveFlg;
	}
private:
	SkinModel model;								//スキンモデル
	SkinModelData modelData;						//スキンモデルデータ
	MeshCollider meshCollider;						//メッシュコライダー
	RigidBody rigidBody;							//剛体

	D3DXVECTOR3 position;							//座標
	D3DXQUATERNION rotation;						//回転
	D3DXVECTOR3 moveSpeed = { 0.0f,0.05f,0.0f };	//移動速度
	float Timer = 0.0f;								//タイマー
	bool moveFlg = false;							//移動フラグ
};

extern MoveFloor2* g_moveFloor2;