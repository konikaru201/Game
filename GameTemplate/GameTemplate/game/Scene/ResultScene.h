#pragma once
#include "myEngine/Graphics/Sprite.h"
#include "myEngine/GameObject/GameObject.h"

class ResultScene : public GameObject {
public:
	//コンストラクタ
	ResultScene();

	//デストラクタ
	~ResultScene();

	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Render();

	//決定ボタンを押したかどうか
	bool GetisDeside() {
		return isDeside;
	}
private:
	Sprite* sprite;				//スプライト
	bool isDeside = false;		//決定ボタンを押したか
	float alpha = 1.0f;
	float timer = 0.0f;
};