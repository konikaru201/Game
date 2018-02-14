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

	//更新される前に一度だけ呼ばれる関数
	bool Start();

	//更新
	void Update();

	//描画
	void Render();

	//シーン切り替えフラグを取得
	bool GetChangeSceneFlag()
	{
		return m_changeScene;
	}
private:
	Sprite* sprite;				//スプライト
	float alpha = 1.0f;			//不透明度。1.0は黒
	float timer = 0.0f;			//タイマー
	bool m_changeScene = false; //シーン切り替えフラグ
};
