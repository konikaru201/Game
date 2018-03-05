#pragma once

#include "myEngine/Physics/BoxCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

class MoveFloor : public GameObject 
{
public:
	//コンストラクタ
	MoveFloor();

	//デストラクタ
	~MoveFloor();

	//初期化
	//pos	座標
	//rot	回転
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//更新する前に一度だけ呼ばれる関数
	bool Start();

	//Update関数より前に呼ばれる更新関数
	void PreUpdate();

	//更新
	void Update();

	//描画
	void Render();
	
	//移動
	void Move();

private:
	SkinModel model;								//スキンモデル
	SkinModelData modelData;						//スキンモデルデータ
	RigidBody rigidBody;							//剛体
	Light light;									//ライト
	D3DXVECTOR3 position;							//座標
	D3DXQUATERNION rotation;						//回転
	D3DXVECTOR3 moveSpeed/* = { 0.07f,0.0f,0.0f }*/;	//移動速度
	float Timer = 0.0f;								//タイマー
	bool moveFlag = false;							//移動フラグ
};