#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Sprite.h"

class Number{
public:
	//コンストラクタ
	Number();

	//デストラクタ
	~Number();

	//初期化
	void Init(D3DXVECTOR2 numPos, D3DXVECTOR2 numSize);

	//数値を設定
	void NumSet(int n);

	//描画
	void Render();
private:
	Sprite* m_number[10];
	int num = 0;
};