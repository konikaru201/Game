#pragma once

#include "myEngine/GameObject/GameObject.h"

class Star : public GameObject
{
public:
	//コンストラクタ
	Star();

	//デストラクタ
	~Star();

	//初期化
	//pos	座標
	//rot	回転
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//更新
	void Update();

	//描画
	void Render();

	//座標を取得
	D3DXVECTOR3 GetPosition()
	{
		return position;
	}

	//スター獲得フラグを取得
	bool GetStar()
	{
		return flag;
	}
private:
	SkinModel model;			//スキンモデル
	SkinModelData modelData;	//スキンモデルデータ
	D3DXVECTOR3	position;		//座標
	D3DXQUATERNION rotation;	//回転
	D3DXVECTOR3 InitPosition;	//初期座標
	bool flag = false;			//スター獲得フラグ
	float moveSpeed = 0.05f;	//移動速度
	float timer = 0.0f;
};