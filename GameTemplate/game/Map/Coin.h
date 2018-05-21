#pragma once

#include "myEngine/GameObject/GameObject.h"

struct CoinInfo {
	D3DXVECTOR3 position;		//座標
	D3DXQUATERNION rotation;	//回転
};

class Coin : public GameObject {
public:
	//コンストラクタ
	Coin();

	//デストラクタ
	~Coin();

	//初期化
	//pos	座標
	//rot	回転
	void Init(int numInstancing);

	bool Start();

	//更新
	void Update();

	//描画
	void Render();

	//シャドウマップ描画
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);

	//インスタンシング描画用のワールド行列を初期化
	void InitInstancingWorldMatrix();

	//インスタンシング描画用のワールド行列を更新
	void UpdateInstancingWorldMatrix();

	//コインの座標と回転を保存
	void SetCoinInfoList(std::list<CoinInfo> coinInfoList)
	{
		m_coinInfoList = coinInfoList;
	}

private:
	SkinModel model;			//スキンモデル
	SkinModelData modelData;	//スキンモデルデータ
	Light light;				//ライト
	//D3DXVECTOR3	position;		//座標
	//D3DXQUATERNION rotation;	//回転
	D3DXVECTOR3 scale;			//拡大率
	D3DXVECTOR3 InitPosition;	//初期座標
	bool flag = false;			//コイン獲得フラグ
	float moveSpeed = 0.05f;	//移動速度
	int m_numInstancing = 0;
	std::list<CoinInfo> m_coinInfoList;
};