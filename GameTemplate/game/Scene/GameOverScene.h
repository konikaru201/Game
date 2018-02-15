#pragma once
#include "myEngine/Graphics/Sprite.h"
#include "myEngine/GameObject/GameObject.h"

namespace {
	const D3DXVECTOR2 gameOverPos = { 0.0f,  200.0f };
	const D3DXVECTOR2 continuePos = { 0.0f, -200.0f };
	const D3DXVECTOR2 stageSelectReturnPos = { 0.0f, -350.0f };
	const D3DXVECTOR2 titleReturnPos = { 0.0f, -500.0f };
	const D3DXVECTOR2 trianglePos = { -580.0f, -200.0f };
}

class GameOverScene : public GameObject {
public:
	//コンストラクタ
	GameOverScene();

	//デストラクタ
	~GameOverScene();

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

	//状態
	enum State {
		state_Continue, //続ける
		state_return,	//ステージセレクトシーンに戻る
		state_End,		//終了
	};

private:
	//スプライト
	Sprite* m_gameOver;				//ゲームオーバー
	Sprite* m_continue;				//コンティニュー
	Sprite* m_stageSelectReturn;	//ステージ選択し直す
	Sprite* m_titleReturn;			//タイトルに戻る
	Sprite* m_triangle;				//三角

	float alpha = 1.0f;				//透明度。0.0で黒
	float timer = 0.0f;				//タイマー
	bool m_changeScene = false;		//シーン切り替えフラグ
	State state = state_Continue;	//状態
	D3DXVECTOR2 m_preTrianglePos;	//三角のスプライト座標保存用変数
};