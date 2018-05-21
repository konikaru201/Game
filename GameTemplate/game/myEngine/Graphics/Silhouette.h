#pragma once

#include "myEngine/GameObject/GameObject.h"

class Silhouette : public GameObject
{
public:
	//コンストラクタ
	Silhouette();

	//デストラクタデストラクタ
	~Silhouette();

	//更新する前に呼ばれる関数
	bool Start();

	//更新
	void Update();

	//描画
	void Render();
};