#pragma once

#include "myEngine/GameObject/GameObject.h"

class Coin : public GameObject {
public:
	//コンストラクタ
	Coin();

	//デストラクタ
	~Coin();

	//初期化
	//pos	座標
	//rot	回転
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//更新
	void Update();

	//描画
	void Render();

	//シャドウマップ描画
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);

	//座標を取得
	const D3DXVECTOR3& GetPosition()
	{
		return position;
	}
private:
	SkinModel model;			//スキンモデル
	SkinModelData modelData;	//スキンモデルデータ
	Light light;
	D3DXVECTOR3	position;		//座標
	D3DXQUATERNION rotation;	//回転
	D3DXVECTOR3 InitPosition;	//初期座標
	bool flag = false;			//コイン獲得フラグ
	float moveSpeed = 0.05f;	//移動速度
};