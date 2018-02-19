#pragma once
#include "myEngine/GameObject/GameObject.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include "StageSelectScene.h"
#include "Scene/GameScene.h"
#include "myEngine/HID/Pad.h"

class SceneManager : public GameObject
{
public:
	//コンストラクタ
	SceneManager();

	//デストラクタ
	~SceneManager();

	//初期化
	bool Start();

	//更新
	void Update();

	//シーンの状態
	enum SceneState {
		stateTitle,
		stateGame,
		stateGameOver,
		stateStageSelect,
	};

	enum FadeStep {
		step_WaitFadeIn,
		step_WaitFadeOut,
		step_normal,		//何もない
	};

	//現在のシーンを取得
	const SceneState& GetScene() {
		return state;
	}

	//シーン切り替えフラグを取得
	bool GetChangeSceneFlag()
	{
		return m_changeScene;
	}
private:
	SceneState state;								//現在のシーン
	FadeStep f_step;								//フェードの状態
	TitleScene* titleScene = nullptr;				//タイトルシーン
	CStageSelectScene* stageSelectScene = nullptr;	//ステージセレクトシーン
	GameScene* gameScene = nullptr;					//ゲームシーン
	bool m_changeScene = false;						//シーン切り替えフラグ
	int m_gameOverSceneStateNumber = 0;				//ゲームオーバーシーンのステート番号
};

extern SceneManager* sceneManager;