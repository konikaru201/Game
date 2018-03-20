#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"

class Building_b : public GameObject {
public:
	//コンストラクタ
	Building_b();
	//デストラクタ
	~Building_b();

	//初期化
	//position		座標
	//rotation		回転
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation);

	//更新
	void Update();

	//描画
	void Render();

private:
	SkinModel model;				//スキンモデル
	SkinModelData modelData;		//スキンモデルデータ
	MeshCollider meshCollider;		//メッシュコライダー
	RigidBody rigidBody;			//剛体
	Light light;					//ライト
	D3DXVECTOR3 m_position;
	D3DXQUATERNION m_rotation;
};