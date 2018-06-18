#include "stdafx.h"
#include "SceneManager.h"
#include "myEngine/Physics/Physics.h"
#include "Fade/Fade.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "Fade/WipeEffect.h"

namespace {
	//コインのスプライトのサイズと座標
	const D3DXVECTOR2 coinSize = { 128.0f,72.0f };
	const D3DXVECTOR2 coinPos = { 920.0f, 600.0f };
	//残機のスプライトのサイズと座標
	const D3DXVECTOR2 remainSize = { 320.0f,240.0f };
	const D3DXVECTOR2 remainPos = { 900.0f,400.0f };
	//×記号のスプライトのサイズと座標
	const D3DXVECTOR2 kakeruSize = { 320.0f,160.0f };
	const D3DXVECTOR2 kakeruPos = { 1030.0f,600.0f };
	const D3DXVECTOR2 kakeru2Pos = { 1030.0f,400.0f };
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	delete m_coin;
	delete m_coinUI;
	delete m_remain;
	delete m_remainNumber;
	delete m_kakeru;
	delete m_kakeru2;
}

bool SceneManager::Start()
{
	//タイトル画面生成
	m_titleScene = goMgr->NewGameObject<TitleScene>();

	m_state = stateTitle;
	m_step = step_WaitFadeIn;

	//スプライトの初期化
	//コインの絵
	m_coin = new Sprite();
	m_coin->Initialize("Assets/sprite/Coin2.png");
	m_coin->SetPosition(coinPos);
	m_coin->SetSize(coinSize);
	//コインの枚数
	m_coinUI = new DisplayCoin();
	m_coinUI->Init(kakeruPos);
	m_coinUI->Start();
	//残機
	m_remain = new Sprite;
	m_remain->Initialize("Assets/sprite/unityChan.png");
	m_remain->SetPosition(remainPos);
	m_remain->SetSize(remainSize);
	//残機数
	m_remainNumber = new RemainNumber;
	m_remainNumber->Init(kakeru2Pos);
	m_remainNumber->Start();
	//×記号
	m_kakeru = new Sprite;
	m_kakeru->Initialize("Assets/sprite/×.png");
	m_kakeru->SetPosition(kakeruPos);
	m_kakeru->SetSize(kakeruSize);
	m_kakeru2 = new Sprite;
	m_kakeru2->Initialize("Assets/sprite/×.png");
	m_kakeru2->SetPosition(kakeru2Pos);
	m_kakeru2->SetSize(kakeruSize);


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
				g_fade->StartFadeIn();
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
			if (!wipeEffect->IsExecute()) {
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
		m_coinUI->Update();
		m_remainNumber->Update();

		break;
	//ゲームシーン
	case stateGame:
		//フェードアウト時
		if (m_step == step_WaitFadeOut) {
			//フェードが終了
			if (!g_fade->IsExecute() && !wipeEffect->IsExecute()) {
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
		m_coinUI->Update();
		m_remainNumber->Update();

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

void SceneManager::PostRender()
{
	if (m_state == stateStageSelect || m_state == stateGame) {
		//アルファブレンディングを有効にする。
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		//コインの絵と枚数を描画
		m_coin->Render();
		m_coinUI->Render();
		//残機の描画
		m_remain->Render();
		m_remainNumber->Render();
		//×記号の描画
		m_kakeru->Render();
		m_kakeru2->Render();
		//アルファブレンディングを無効にする。
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}
}
