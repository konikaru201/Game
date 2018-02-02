#include "stdafx.h"
#include "SceneManager.h"
#include "Scene/GameScene.h"
#include "myEngine/Physics/Physics.h"
#include "../Fade/Fade.h"
#include "myEngine/GameObject/GameObjectManager.h"

SceneManager::SceneManager()
{
	//タイトル画面生成
	titleScene = goMgr->NewGameObject<TitleScene>();

	state = stateTitle;
	f_step = step_normal;

	titleScene->Initialize();
}

SceneManager::~SceneManager()
{
	delete titleScene;
	titleScene = nullptr;
	delete result;
	result = nullptr;
	delete gameScene;
	gameScene = nullptr;
}

bool SceneManager::Start()
{
	return true;
}

void SceneManager::Update()
{
	//フェードイン中
	if (f_step == step_WaitFadeIn)
	{
		//フェードが終了
		if (!g_fade->IsExecute())
		{
			f_step = step_normal;
		}
	}

	switch (state)
	{
	//タイトル画面のとき
	case stateTitle:
		if (f_step == step_WaitFadeOut) {
			//フェードが終了
			if (!g_fade->IsExecute()) {
				//タイトルシーンを削除
				titleScene->SetisDead();
				titleScene = nullptr;
				//ゲームシーンに遷移
				gameScene = new GameScene;
				gameScene->Start();
				state = stateGame;

				f_step = step_WaitFadeIn;
			}
		}
		else if (f_step == step_normal) {
			//決定した
			if (titleScene->GetisDeside()) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
		}

		break;
	//ゲームシーンのとき
	case stateGame:
		//フェードアウト時
		if (f_step == step_WaitFadeOut) {
			//フェードが終了
			if (!g_fade->IsExecute()) {
				if (gameScene->IsStep() == GameScene::step_GameOver) {
					//リザルトに遷移
					result = goMgr->NewGameObject<ResultScene>();
					result->Initialize();
					state = stateResult;
				}
				
				gameScene->Release();
				gameScene = nullptr;
				f_step = step_WaitFadeIn;
			}
		}
		//通常時
		else if (f_step == step_normal) {
			GameScene::Step g_step = gameScene->IsStep();
			if (g_step == GameScene::step_GameClear || g_step == GameScene::step_GameOver) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
			gameScene->Update();
		}
		break;
		//ゲームオーバーのとき
	case stateResult:
		//フェードアウト時
		if (f_step == step_WaitFadeOut) {
			//フェードが終了
			if (!g_fade->IsExecute()) {
				result->SetisDead();
				result = nullptr;
				f_step = step_WaitFadeIn;
				//タイトルに遷移
				titleScene = goMgr->NewGameObject<TitleScene>();
				titleScene->Initialize();
				state = stateTitle;
			}
		}
		else if(f_step == step_normal){
			if (pad->IsTrigger(pad->enButtonA)) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
		}
		break;
	}
}