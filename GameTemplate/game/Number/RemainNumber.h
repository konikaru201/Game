#pragma once

#include "Number.h"

class RemainNumber : public GameObject
{
public:
	//コンストラクタ
	RemainNumber();

	//デストラクタ
	~RemainNumber();

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

	void RemainCount(int count)
	{
		m_remainNum += count;
	}

	//残機数を獲得
	int GetRemainNum()
	{
		return m_remainNum;
	}
private:
	Number*		num[3];						//数字
	D3DXVECTOR2 m_position = { 0.0f,0.0f }; //座標
	int			m_remainNum = 3;			//残機数
};

extern RemainNumber* remainNumber;