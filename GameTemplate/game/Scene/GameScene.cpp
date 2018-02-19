#include "stdafx.h"
#include "GameScene.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "Fade/Fade.h"
#include "myEngine/Timer/Timer.h"

SMapInfo Stage2[] = {
#include "locationinfo/stage2.h"
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
	StageCreate();

	depthStencilRender = goMgr->NewGameObject<DepthStencilRender>();	//シルエット生成
	player = goMgr->NewGameObject<Player>();			//プレイヤー生成
	gameCamera = goMgr->NewGameObject<GameCamera>();	//カメラ生成

	return true;
}
/*!
* @brief	更新。
*/
void GameScene::Update()
{
	switch (step){
	//ステージ読み込みが終了
	case step_StageLoad:
		g_fade->StartFadeIn();
		step = step_WaitFadeIn;
		break;

	//フェードイン時
	case step_WaitFadeIn:
		//フェードが終了
		if (!g_fade->IsExecute()) {
			step = step_normal;
		}
		break;

	//通常時
	case step_normal:
		//プレイヤー死亡時
		if (player->GetPlayerDead()) {
			bgmSource->SetisDead();
			bgmSource = nullptr;
			gameOverScene = goMgr->NewGameObject<GameOverScene>();
			step = step_GameOver;
		}
		//スター獲得時
		else if (player->GetStarAnimationEnd()) {
			bgmSource->SetisDead();
			bgmSource = nullptr;
			g_fade->StartFadeOut();
			step = step_StageClear;
		}
		g_physicsWorld->Update();
		break;
	//ゲームオーバー時
	case step_GameOver:
		//ゲームオーバーシーンが終了
		if (gameOverScene != nullptr && gameOverScene->GetGameOverSceneEnd()) {
			m_gameOverSceneStateNumber = gameOverScene->GetStateNumber();
			g_fade->StartFadeOut();
			m_gameOverSceneEnd = true;
			gameOverScene->SetisDead();
			gameOverScene = nullptr;
		}
		break;
	//ステージクリア時
	case step_StageClear:
		//フェードが終了
		if (!g_fade->IsExecute()) {
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

void GameScene::StageCreate()
{
	int numObject = sizeof(Stage2) / sizeof(Stage2[0]);

	map->Create(Stage2, numObject);

	bgmSource = goMgr->NewGameObject<CSoundSource>();
	bgmSource->InitStreaming("Assets/sound/bgm_2.wav");
	bgmSource->Play(true);

	step = step_StageLoad;
}

void GameScene::Release()
{
	player->SetisDead();
	player = nullptr;
	depthStencilRender->SetisDead();
	depthStencilRender = nullptr;
	gameCamera->SetisDead();
	gameCamera = nullptr;
	map->SetisDead();
	map = nullptr;
}
