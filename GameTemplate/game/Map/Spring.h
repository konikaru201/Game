#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

class Spring : public GameObject
{
public:
	//コンストラクタ
	Spring();

	//デストラクタ
	~Spring();

	//初期化
	//pos	座標
	//rot	回転
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	bool Start();

	//更新
	void Update();

	//描画
	void Render();

	//プレイヤーとの当たり判定
	void CollisionDetection();

	//移動速度を取得
	const D3DXVECTOR3& GetMoveSpeed()
	{
		return m_jumpSpeed;
	}

private:
	SkinModel m_model;									//スキンモデル
	SkinModelData m_modelData;							//スキンモデルデータ
	MeshCollider m_meshCollider;						//メッシュコライダー
	RigidBody m_rigidBody;								//剛体
	Light light;										//ライト
	D3DXVECTOR3 m_position;								//座標
	D3DXQUATERNION m_rotation;							//回転
	D3DXVECTOR3 m_jumpSpeed = { 0.0f, 20.0f, 0.0f };	//ジャンプ速度

	D3DXMATRIX parentWorldMatrix;						//親のワールド行列
	D3DXVECTOR3 childPosition = { 0.0f,0.0f,0.0f };		//親のローカル座標からみた座標
	bool moveFloor2Find = false;
	D3DXVECTOR3 moveFloor2Position = { 0.0f,0.0f,0.0f };
};