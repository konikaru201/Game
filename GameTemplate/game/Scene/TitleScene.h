#pragma once
#include "myEngine/Graphics/Sprite.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Camera.h"

class TitleScene : public GameObject{
public:
	//コンストラクタ
	TitleScene();

	//デストラクタ
	~TitleScene();

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
	float alpha = 1.0f;			//不透明度。1.0は黒
	float timer = 0.0f;			//タイマー
};
