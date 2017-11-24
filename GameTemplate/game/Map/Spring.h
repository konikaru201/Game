#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"

class Spring : public GameObject
{
public:
	Spring();
	~Spring();
	//初期化
	//pos	座標
	//rot	回転
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//更新
	void Update();

	//描画
	void Render();

	//移動
	void Move();

	//移動速度を取得
	D3DXVECTOR3& GetMoveSpeed()
	{
		return moveSpeed;
	}

	////移動フラグを取得
	//bool GetMoveFlg()
	//{
	//	return MoveFlg;
	//}
private:
	SkinModel model;								//スキンモデル
	SkinModelData modelData;						//スキンモデルデータ
	MeshCollider meshCollider;						//メッシュコライダー
	RigidBody rigidBody;							//剛体

	D3DXVECTOR3 position;							//座標
	D3DXQUATERNION rotation;						//回転
	D3DXVECTOR3 moveSpeed = { 0.0f, 20.0f, 0.0f };	//移動速度
	bool MoveFlg = false;

};