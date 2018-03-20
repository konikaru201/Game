#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"
#include "myEngine/Graphics/ParticleEmitter.h"
#include "myEngine/Physics/RigidBody.h"

class Killer : public GameObject {
public:
	//コンストラクタ
	Killer();

	//デストラクタ
	~Killer();

	//初期化
	//pos	座標
	//rot	回転
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//更新
	void Update();

	//描画
	void Render();

	//移動
	D3DXVECTOR3 Move();

	//プレイヤーとの当たり判定
	void CollisionDetection(float Length , const D3DXVECTOR3& ToPlayer);

	//影の描画
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);

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
	enum State {
		State_Search,	//探索
		State_Find,		//発見
		State_Miss,		//見失う
		State_Dead,		//死亡
		State_Hit,		//プレイヤーにヒット
	};

	State				state = State_Search;				//状態

	SkinModel			model;								//スキンモデル
	SkinModelData		modelData;							//スキンモデルデータ
	Light				light;								//ライト
	D3DXVECTOR3			position;							//座標
	D3DXQUATERNION		rotation;							//回転
	D3DXVECTOR3			initPosition;						//初期位置
	D3DXQUATERNION		initRotation;						//初期回転
	float				moveLimitLine[4];					//移動限界ライン
	RigidBody			rigidBody;							//剛体
	D3DXVECTOR3			moveDir = { 0.0f,0.0f,0.0f };		//見失ったときの移動方向
	const float			moveSpeed = 5.5f;					//移動速度
	bool				isDead = false;						//死亡フラグ
	bool				isRespawn = false;					//リスポーンフラグ
	float				timer = 0.0f;						//タイマー
	bool				m_hitPlayer = false;				//プレイヤーに当たったフラグ
	CParticleEmitter	particleEmitter;					//パーティクル生成
};