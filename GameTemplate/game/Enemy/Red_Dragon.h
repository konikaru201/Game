#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Graphics/ParticleEmitter.h"

class Red_Dragon : public GameObject
{
public:
	//コンストラクタ
	Red_Dragon();

	//デストラクタ
	~Red_Dragon();

	//初期化
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//更新
	void Update();

	//描画
	void Render();

	//移動
	D3DXVECTOR3 Move();

	//プレイヤーとの当たり判定
	void CollisionDetection(float Length, const D3DXVECTOR3& ToPlayer);

	//モデルの向きを取得
	D3DXVECTOR3 GetDirection()
	{
		D3DXMATRIX matrix = model.GetWorldMatrix();
		D3DXVECTOR3 direction;
		direction.x = matrix.m[2][0];
		direction.y = matrix.m[2][1];
		direction.z = matrix.m[2][2];
		D3DXVec3Normalize(&direction, &direction);
		return direction;
	}
private:
	enum AnimationNo {
		AnimationWait,		//待機
		AnimationRun,		//走り移動
		AnimationAttack,	//攻撃
	};

	enum State {
		State_Wait,		//待機
		State_Move,		//移動
		State_Find,		//発見
		State_Miss,		//見失う
		State_Attack,	//攻撃
		State_Dead,		//死亡
		State_Hit,		//プレイヤーにヒット
	};

	State state = State_Wait;
	AnimationNo currentAnim;
	AnimationNo prevAnim;

	SkinModel			model;							//スキンモデル
	SkinModelData		modelData;						//スキンモデルデータ
	D3DXVECTOR3			position;						//座標
	D3DXVECTOR3			initPosition;					//初期座標
	D3DXQUATERNION		rotation;						//回転
	RigidBody			rigidBody;						//剛体
	Animation			animation;						//アニメーション
	D3DXVECTOR3			moveDir = { 0.0f,0.0f,0.0f };	//移動方向
	D3DXVECTOR3			up = { 0.0f,1.0f,0.0f };		//上方向
	float				moveSpeed = 2.0f;				//移動速度
	D3DXMATRIX*			matrix;							//ボーンのワールド行列
	float				timer = 0.0f;					//タイマー
	float				soundTimer = 0.0f;				//音のタイマー
	D3DXVECTOR3			XDir = { 1.0f,0.0f,0.0f };		//X方向
	bool				findAgainFlag = false;			//攻撃後に視界内にプレイヤーがいるか
	bool				changeDir = true;				//方向転換のフラグ
	CParticleEmitter	particleEmitter;				//パーティクル生成
	bool				m_hitPlayer = false;			//プレイヤーに当たったフラグ
	bool				isDead = false;					//死亡フラグ
};