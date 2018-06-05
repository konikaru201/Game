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
	m_titleScene = goMgr->NewGameObject<TitleScene>();

	m_state = stateTitle;
	m_step = step_normal;

	return true;
}

void SceneManager::Update()
{
	//フェードイン中
	if (m_step == step_WaitFadeIn)
	{
		//フェードインが終了
		if (!g_fade->IsExecute())
		{
			m_step = step_normal;
		}
	}

	m_changeScene = false;

	switch (m_state)
	{
	//タイトルシーン
	case stateTitle:
		//フェードアウト時
		if (m_step == step_WaitFadeOut) {
			//フェードが終了
			if (!g_fade->IsExecute()) {
				//タイトルシーンを削除
				m_titleScene->SetisDead();
				m_titleScene = nullptr;
				//ステージセレクトシーンに遷移
				m_stageSelectScene = goMgr->NewGameObject<CStageSelectScene>();
				m_state = stateStageSelect;
				m_step = step_WaitFadeIn;
			}
		}
		//通常時
		else if (m_step == step_normal) {
			//シーン切り替え時フェードアウト
			if (m_titleScene->GetChangeSceneFlag()) {
				g_fade->StartFadeOut();
				m_step = step_WaitFadeOut;
			}
		}

		break;
	//ステージセレクトシーン
	case stateStageSelect:
		//フェードアウト時
		if (m_step == step_WaitFadeOut) {
			//フェードが終了
			if (!g_fade->IsExecute()) {
				//ステージセレクトシーンを削除
				m_stageSelectScene->Release();
				m_stageSelectScene->SetisDead();
				m_stageSelectScene = nullptr;
				//ゲームシーンに遷移
				m_gameScene = goMgr->NewGameObject<GameScene>();
				m_gameScene->SetStageNumber(m_stageNumber);
				m_state = stateGame;
				
				m_step = step_WaitFadeIn;
			}
		}
		//通常時
		else if (m_step == step_normal) {
			//フェードアウト待ち
			if (m_stageSelectScene->GetWaitFadeOut()) {
				m_step = step_WaitFadeOut;
				m_changeScene = true;
				m_stageNumber = m_stageSelectScene->GetStageNumber();
			}
		}
		break;
	//ゲームシーン
	case stateGame:
		//フェードアウト時
		if (m_step == step_WaitFadeOut) {
			//フェードが終了
			if (!g_fade->IsExecute()) {
				//ゲームシーンの現在の状態を取得
				GameScene::Step g_step = m_gameScene->IsStep();
				//ステージクリア時
				if (g_step == GameScene::step_StageClear) {
					//ステージセレクトシーンに遷移
					m_stageSelectScene = goMgr->NewGameObject<CStageSelectScene>();
					m_state = stateStageSelect;
					m_step = step_WaitFadeIn;
					//ゲームシーンを削除
					m_gameScene->Release();
					m_gameScene->SetisDead();
					m_gameScene = nullptr;
				}
				//ゲームオーバー時
				if (g_step == GameScene::step_GameOver) {
					m_changeScene = true;
					m_state = stateGameOver;
					m_step = step_WaitFadeIn;
				}
			}
		}
		//通常時
		else if (m_step == step_normal) {
			//ステージクリアになった
			if (m_gameScene->GetStageClearFlag()) 
			{
				m_step = step_WaitFadeOut;
				m_changeScene = true;
			}
			//ゲームオーバーになった
			if (m_gameScene->GetGameOverEnd()) {
				m_step = step_WaitFadeOut;
			}
		}
		break;
	//ゲームオーバーシーン
	case stateGameOver:
		//選択したシーンの番号を取得
		m_gameOverSceneStateNumber = m_gameScene->GetGameOverSceneStateNumber();
		//ゲームシーンを削除
		m_gameScene->Release();
		m_gameScene->SetisDead();
		m_gameScene = nullptr;
		//コンティニュー
		if (m_gameOverSceneStateNumber == 0) {
			//ゲームシーンを作り直す
			m_gameScene = goMgr->NewGameObject<GameScene>();
			m_gameScene->SetStageNumber(m_stageNumber);
			m_state = stateGame;
		}
		//ステージ選択に戻る
		else if (m_gameOverSceneStateNumber == 1) {
			//ステージセレクトシーンに遷移
			m_stageSelectScene = goMgr->NewGameObject<CStageSelectScene>();
			m_state = stateStageSelect;
		}
		//タイトルに戻る
		else {
			//タイトルシーンに遷移
			m_titleScene = goMgr->NewGameObject<TitleScene>();
			m_state = stateTitle;
		}
		
		m_step = step_WaitFadeIn;

		break;
	}
}
