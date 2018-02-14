#pragma once

#include "Number.h"

class DisplayCoin : public GameObject
{
public:
	//コンストラクタ
	DisplayCoin();

	//デストラクタ
	~DisplayCoin();

	//初期化
	void Init(D3DXVECTOR2 position);

	//更新する前に呼ばれる関数
	bool Start();

	//更新
	void Update();

	//削除
	void DeleteNum();

	//描画
	void Render();

	//コインの枚数をカウント
	void CoinCount(int count)
	{
		m_coinNum += count;
	}
private:
	Number*		num[2];						//数字
	D3DXVECTOR2 m_position = { 0.0f,0.0f }; //座標
	int			m_coinNum = 0;				//コインの枚数
};

extern DisplayCoin* displayCoin;