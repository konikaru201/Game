#pragma once
#include "myEngine/GameObject/GameObject.h"
#include "TitleScene.h"
#include "ResultScene.h"
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
		stateResult,
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
	ResultScene* resultScene = nullptr;				//リザルトシーン
	CStageSelectScene* stageSelectScene = nullptr;	//ステージセレクトシーン
	GameScene* gameScene = nullptr;					//ゲームシーン
	bool m_changeScene = false;						//シーン切り替えフラグ
};

extern SceneManager* sceneManager;