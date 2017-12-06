#pragma once

#include "Number.h"

class DisplayCoin : public GameObject
{
public:
	//コンストラクタ
	DisplayCoin();

	//デストラクタ
	~DisplayCoin();

	//更新する前に呼ばれる関数
	bool Start();

	//更新
	void Update();

	//削除
	void DeleteNum();

	//描画
	void Render();
private:
	Number* num[2];
};