#pragma once

#include "myEngine/Physics/CharacterController.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

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
	CharacterController characterController;				//キャラクターコントローラー
	Light				light;								//ライト
	D3DXVECTOR3			position;							//座標
	D3DXQUATERNION		rotation;							//回転
	D3DXVECTOR3			InitPosition;						//初期位置
	float				moveLimitLine[4];					//移動限界ライン
	RigidBody			rigidBody;							//剛体
	D3DXVECTOR3			moveDir = { 0.0f,0.0f,0.0f };		//見失ったときの移動方向
	const float			moveSpeed = 4.0f;					//移動速度
	bool				isDead = false;						//死亡フラグ
	float				timer = 0.0f;						//タイマー
	bool				m_hitPlayer = false;				//プレイヤーに当たったフラグ
};