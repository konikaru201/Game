#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Physics/BoxCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Graphics/Light.h"

class Floor : public GameObject{
public:
	Floor();

	~Floor();

	//初期化
	//pos	座標
	//rot	回転
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//更新
	void Update();

	//描画
	void Render();

private:
	SkinModel model;								//スキンモデル
	SkinModelData modelData;						//スキンモデルデータ
	RigidBody rigidBody;							//剛体
	Light light;									//ライト
	D3DXVECTOR3 position;							//座標
	D3DXQUATERNION rotation;						//回転
};