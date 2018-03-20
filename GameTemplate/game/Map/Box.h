#pragma once

#include "myEngine/Physics/BoxCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

class Box : public GameObject
{
public:
	//コンストラクタ
	Box();

	//デストラクタ
	~Box();

	//初期化
	//pos	座標
	//rot	回転
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//更新
	void Update();

	//描画
	void Render();

	void PostRender();
private:
	enum State {
		Entity,		//実体
		Clear		//透明
	};
	State m_state = Entity;

	SkinModel model;								//スキンモデル
	SkinModelData modelData;						//スキンモデルデータ
	RigidBody rigidBody;							//剛体
	Light light;									//ライト
	D3DXVECTOR3 position;							//座標
	D3DXQUATERNION rotation;						//回転
	float m_timer = 0.0f;			//タイマー
	float m_alpha = 1.0f;			//不透明度。0.0で透明
	const float ALPHA_TIME = 0.5f;
	float m_alphaTimer = 0.0f;
};