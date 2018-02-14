#include "stdafx.h"
#include "GameScene.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "../Fade/Fade.h"
#include "../myEngine/Timer/Timer.h"

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
	if (step == step_WaitFadeOut) {		
		//マップ生成
		map = goMgr->NewGameObject<Map>();
		//ステージ作成
		StageCreate();

		depthStencilRender = goMgr->NewGameObject<DepthStencilRender>();	//シルエット生成
		player = goMgr->NewGameObject<Player>();			//プレイヤー生成
		gameCamera = goMgr->NewGameObject<GameCamera>();	//カメラ生成
		
		return false;
	}
	else {
		step = step_WaitFadeIn;
		g_fade->StartFadeIn();
	}

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
			g_fade->StartFadeOut();
			step = step_GameOver;
		}
		//スター獲得時
		else if (player->GetStarAnimationEnd()) {
			g_fade->StartFadeOut();
			step = step_StageClear;
		}
		g_physicsWorld->Update();
		break;
	//フェードアウト時
	case step_WaitFadeOut:
		break;
	//ゲームオーバー時
	case step_GameOver:
		//フェードが終了
		if (!g_fade->IsExecute()) {
			m_waitFadeOut = true;
		}
		break;
	//ステージクリア時
	case step_StageClear:
		//フェードが終了
		if (!g_fade->IsExecute()) {
			m_waitFadeOut = true;
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
	bgmSource->SetisDead();
	bgmSource = nullptr;
}
