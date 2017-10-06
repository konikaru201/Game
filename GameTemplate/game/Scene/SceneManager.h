#pragma once
#include "myEngine/GameObject/GameObject.h"
#include "TitleScene.h"
#include "ResultScene.h"
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
	};

	enum FadeStep {
		step_WaitFadeIn,
		step_WaitFadeOut,
		step_normal,		//何もない
	};

	//現在のシーンを取得
	SceneState GetScene() {
		return state;
	}
private:
	SceneState state;						//現在のシーン
	FadeStep f_step;
	TitleScene* titleScene = nullptr;		//タイトルシーン
	ResultScene* result = nullptr;
};

extern SceneManager* sceneManager;