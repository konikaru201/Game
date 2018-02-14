#include "stdafx.h"
#include "SceneManager.h"
#include "myEngine/Physics/Physics.h"
#include "../Fade/Fade.h"
#include "myEngine/GameObject/GameObjectManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

bool SceneManager::Start()
{
	//タイトル画面生成
	titleScene = goMgr->NewGameObject<TitleScene>();

	state = stateTitle;
	f_step = step_normal;

	return true;
}

void SceneManager::Update()
{
	//フェードイン中
	if (f_step == step_WaitFadeIn)
	{
		//フェードインが終了
		if (!g_fade->IsExecute())
		{
			f_step = step_normal;
		}
	}

	m_changeScene = false;

	switch (state)
	{
	//タイトルシーン
	case stateTitle:
		//フェードアウト時
		if (f_step == step_WaitFadeOut) {
			//フェードが終了
			if (!g_fade->IsExecute()) {
				//タイトルシーンを削除
				titleScene->SetisDead();
				titleScene = nullptr;
				//ステージセレクトシーンに遷移
				stageSelectScene = goMgr->NewGameObject<CStageSelectScene>();
				state = stateStageSelect;
				f_step = step_WaitFadeIn;
			}
		}
		//通常時
		else if (f_step == step_normal) {
			//シーン切り替え時フェードアウト
			if (titleScene->GetChangeSceneFlag()) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
		}

		break;
	//ステージセレクトシーン
	case stateStageSelect:
		//フェードアウト時
		if (f_step == step_WaitFadeOut) {
			//フェードが終了
			if (!g_fade->IsExecute()) {
				//ステージセレクトシーンを削除
				stageSelectScene->Release();
				stageSelectScene->SetisDead();
				stageSelectScene = nullptr;
				//ゲームシーンに遷移
				gameScene = goMgr->NewGameObject<GameScene>();
				state = stateGame;
				f_step = step_WaitFadeIn;
			}
		}
		//通常時
		else if (f_step == step_normal) {
			//フェードアウト待ち
			if (stageSelectScene->GetWaitFadeOut()) {
				//g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
				m_changeScene = true;
			}
		}
		break;
	//ゲームシーン
	case stateGame:
		//フェードアウト時
		if (f_step == step_WaitFadeOut) {
			//フェードが終了
			if (!g_fade->IsExecute()) {
				//ゲームシーンの現在の状態を取得
				GameScene::Step g_step = gameScene->IsStep();
				//ゲームシーンを削除
				gameScene->Release();
				gameScene->SetisDead();
				gameScene = nullptr;
				//ゲームオーバー時
				if (g_step == GameScene::step_GameOver) {
					//リザルトシーンに遷移
					resultScene = goMgr->NewGameObject<ResultScene>();
					state = stateResult;
					f_step = step_WaitFadeIn;
				}
				//ステージクリア時
				else if (g_step == GameScene::step_StageClear) {
					//ステージセレクトシーンに遷移
					stageSelectScene = goMgr->NewGameObject<CStageSelectScene>();
					state = stateStageSelect;
					f_step = step_WaitFadeIn;
				}
			}
		}
		//通常時
		else if (f_step == step_normal) {
			////ゲームシーンの現在の状態を取得
			//GameScene::Step g_step = gameScene->IsStep();
			//ゲームオーバーかステージクリアになるとフェードアウト
			if (gameScene->GetWaitFadeOut()/*g_step == GameScene::step_GameOver || g_step == GameScene::step_StageClear*/) {
				f_step = step_WaitFadeOut;
				m_changeScene = true;
			}
		}
		break;
	//リザルトシーン
	case stateResult:
		//フェードアウト時
		if (f_step == step_WaitFadeOut) {
			//フェードが終了
			if (!g_fade->IsExecute()) {
				//リザルトシーンを削除
				resultScene->SetisDead();
				resultScene = nullptr;
				//ゲームシーンに遷移
				gameScene = goMgr->NewGameObject<GameScene>();
				state = stateGame;
				f_step = step_WaitFadeIn;
			}
		}
		//通常時
		else if(f_step == step_normal){
			//シーン切り替え時フェードアウト
			if (resultScene->GetChangeSceneFlag()) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
		}
		break;
	}
}
