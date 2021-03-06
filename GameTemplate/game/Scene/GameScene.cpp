#include "stdafx.h"
#include "GameScene.h"
#include "SceneManager.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "Fade/Fade.h"
#include "myEngine/Timer/Timer.h"
#include "Fade/WipeEffect.h"

SMapInfo Stage1[] = {
#include "locationinfo/stage2.h"
};

SMapInfo Stage2[] = {
#include "locationinfo/stage3.h"
};

SMapInfo Stage3[] = {
#include "locationinfo/stage4.h"
};

/*!
* @brief	コンストラクタ。
*/
GameScene::GameScene()
{
}
/*!
* @brief	デストラクタ。
*/
GameScene::~GameScene()
{
}
/*!
* @brief	ゲームが起動してから一度だけ呼ばれる関数。
*/
bool GameScene::Start()
{
	//マップ生成
	map = goMgr->NewGameObject<Map>();
	//ステージ作成
	StageCreate(m_stageNumber);

	m_silhouette = goMgr->NewGameObject<Silhouette>();	//シルエット生成
	player = goMgr->NewGameObject<Player>();			//プレイヤー生成
	gameCamera = goMgr->NewGameObject<GameCamera>();	//カメラ生成

	return true;
}
/*!
* @brief	更新。
*/
void GameScene::Update()
{
	switch (m_step){
	//ステージ読み込みが終了
	case step_StageLoad:
		wipeEffect->StartWipeIn();
		m_step = step_WaitFadeIn;
		break;

	//フェードイン時
	case step_WaitFadeIn:
		//ワイプエフェクトが終了
		if (!wipeEffect->IsExecute()) {
			m_step = step_normal;
		}
		break;

	//通常時
	case step_normal:
		//プレイヤー死亡時
		if (player->GetPlayerDead()) {
			m_bgmSource->SetisDead();
			m_bgmSource = nullptr;
			if (sceneManager->GetRemainNumber()->GetRemainNum() <= 0) {
				m_gameOverScene = goMgr->NewGameObject<GameOverScene>();
				m_restart = false;
			}
			m_step = step_GameOver;
		}
		//スター獲得時
		else if (player->GetAnimationEnd()) {
			m_bgmSource->SetisDead();
			m_bgmSource = nullptr;
			wipeEffect->StartWipeOut();
			m_step = step_StageClear;
		}
		g_physicsWorld->Update();
		break;
	//ゲームオーバー時
	case step_GameOver:
		//残機数が０でないならリスタート
		if (m_restart) {
			wipeEffect->StartWipeOut();
			m_gameOverSceneEnd = true;
			m_restart = false;
		}
		//ゲームオーバーシーンが終了
		else if (m_gameOverScene != nullptr && m_gameOverScene->GetGameOverSceneEnd())
		{
			m_gameOverSceneStateNumber = m_gameOverScene->GetStateNumber();
			if (m_gameOverSceneStateNumber == m_gameOverScene->state_Continue 
				|| m_gameOverSceneStateNumber == m_gameOverScene->state_return) 
			{
				wipeEffect->StartWipeOut();
			}
			else {
				g_fade->StartFadeOut();
			}
			m_gameOverSceneEnd = true;
			m_gameOverScene->SetisDead();
			m_gameOverScene = nullptr;
		}
		g_physicsWorld->Update();
		break;
	//ステージクリア時
	case step_StageClear:
		//ワイプエフェクトが終了
		if (!wipeEffect->IsExecute()) {
			m_stageClearFlag = true;
		}
		break;
	}
}
/*!
* @brief	描画。
*/
void GameScene::Render()
{
}

void GameScene::StageCreate(int number)
{
	//ステージ１
	if(number == 1)
	{
		int numObject = sizeof(Stage1) / sizeof(Stage1[0]);

		map->Create(Stage1, numObject);

		m_bgmSource = goMgr->NewGameObject<CSoundSource>();
		m_bgmSource->InitStreaming("Assets/sound/bgm_2.wav");
		m_bgmSource->Play(true);
	}
	//ステージ２
	else if (number == 2) {
		int numObject = sizeof(Stage2) / sizeof(Stage2[0]);

		map->Create(Stage2, numObject);

		m_bgmSource = goMgr->NewGameObject<CSoundSource>();
		m_bgmSource->InitStreaming("Assets/sound/bgm_2.wav");
		m_bgmSource->Play(true);
	}
	//ステージ３
	else if (number == 3) {
		int numObject = sizeof(Stage3) / sizeof(Stage3[0]);

		map->Create(Stage3, numObject);

		m_bgmSource = goMgr->NewGameObject<CSoundSource>();
		m_bgmSource->InitStreaming("Assets/sound/bgm_2.wav");
		m_bgmSource->Play(true);
	}

	m_step = step_StageLoad;
}

void GameScene::Release()
{
	player->SetisDead();
	player = nullptr;
	m_silhouette->SetisDead();
	m_silhouette = nullptr;
	gameCamera->SetisDead();
	gameCamera = nullptr;
	map->SetisDead();
	map = nullptr;
}

void GameScene::SetStageNumber(int number)
{
	m_stageNumber = number;
}
