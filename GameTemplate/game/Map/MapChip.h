#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"

class MapChip : public GameObject
{
public:
	//コンストラクタ
	MapChip();

	//デストラクタ
	~MapChip();

	//初期化
	//modelName		モデルネーム
	//position		座標
	//rotation		回転
	void Init(const char* modelName, D3DXVECTOR3 position, D3DXQUATERNION rotation);

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
};

