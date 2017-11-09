#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"

class Block : public GameObject
{
public:
	//コンストラクタ
	Block();

	//デストラクタ
	~Block();

	//初期化
	//pos	座標
	//rot	回転
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	bool Start();

	//更新
	void Update();

	//描画
	void Render();

	D3DXMATRIX GetWorldMatrix()
	{
		return model.GetWorldMatrix();
	}

	D3DXMATRIX GetRotationMatrix()
	{
		return model.GetRotationMatrix();
	}
private:
	SkinModel model;								//スキンモデル
	SkinModelData modelData;						//スキンモデルデータ
	MeshCollider meshCollider;						//メッシュコライダー
	RigidBody rigidBody;							//剛体
	D3DXVECTOR3 rotationAxis;
	D3DXVECTOR3 position;							//座標
	D3DXQUATERNION rotation;						//回転
};