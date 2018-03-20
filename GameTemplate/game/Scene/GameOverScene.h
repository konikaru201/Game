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

	void PostRender();

	//ゲームオーバーシーン終了フラグを取得
	bool GetGameOverSceneEnd()
	{
		return m_gameOverSceneEnd;
	}

	//状態
	enum State {
		state_Continue, //続ける
		state_return,	//ステージセレクトシーンに戻る
		state_End,		//終了
	};

	//状態を数字で取得。
	//0はコンティニュー。1はステージ選択に戻る。2はタイトルに戻る。
	int GetStateNumber()
	{
		return m_stateNumber;
	}

private:
	//スプライト
	Sprite* m_gameOver;				//ゲームオーバー
	Sprite* m_continue;				//コンティニュー
	Sprite* m_stageSelectReturn;	//ステージ選択し直す
	Sprite* m_titleReturn;			//タイトルに戻る
	Sprite* m_triangle;				//三角
	Sprite* m_background;			//背景

	const float FADE_TIME = 1.0f;	//フェードする時間
	float m_alpha = 0.0f;			//不透明度。1.0は黒
	float m_timer = 0.0f;			//タイマー
	bool m_gameOverSceneEnd = false;//ゲームオーバーシーン終了フラグ
	State m_state = state_Continue;	//状態
	int m_stateNumber = 0;			//状態の番号。0はコンティニュー。1はステージ選択に戻る。2はタイトルに戻る。
	D3DXVECTOR2 m_preGameOverPos;	//ゲームオーバーのスプライト座標保存用変数
	D3DXVECTOR2 m_preTrianglePos;	//三角のスプライト座標保存用変数
	bool m_gameOverSet = false;		//ゲームオーバーが表示されたか
};