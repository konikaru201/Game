#include "stdafx.h"
#include "GameScene.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "../Fade/Fade.h"
#include "../myEngine/Timer/Timer.h"

GameScene* gameScene;

SMapInfo Stage1[] = {
#include "locationinfo/stage1.h"
};

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
	//delete map;
	map = nullptr;
	//delete g_player;
	g_player = nullptr;
	delete displayCoin;
	displayCoin = nullptr;
	delete CoinNum;
	CoinNum = nullptr;
	//delete gameCamera;
	gameCamera = nullptr;
}
/*!
* @brief	ゲームが起動してから一度だけ呼ばれる関数。
*/
bool GameScene::Start()
{
	if (step == step_WaitFadeOut) {
	//ライトを初期化
		light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
		light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
		light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
		light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

		light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
		light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
		light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
		light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
		light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
		
		//スプライトを初期化
		InitSprite();

		g_physicsWorld = new PhysicsWorld;
		g_physicsWorld->Init();
		
		map = goMgr->NewGameObject<Map>();					//マップ生成
		ChengeStage = false;
		finishFadeOut = true;
		currentStage = en_Stage1;
		//マップ作成
		StageCreate();

		depthStencilRender = goMgr->NewGameObject<DepthStencilRender>();
		g_player = goMgr->NewGameObject<Player>();			//プレイヤー生成
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
		if (pad->IsTrigger(pad->enButtonStart)) {
			g_fade->StartFadeOut();
			step = step_WaitFadeOut;
			return;
		}
		if (g_player->GetState() == g_player->State_Dead) {
			step = step_GameOver;
		}
		g_physicsWorld->Update();
		displayCoin->Update();
		break;

	case step_WaitFadeOut:
		if (ChengeStage) {
			//ステージ切り替え
			currentStage = nextStage;
			ChengeStage = false;
			StageCreate();
			depthStencilRender = goMgr->NewGameObject<DepthStencilRender>();
			g_player = goMgr->NewGameObject<Player>();
			gameCamera = goMgr->NewGameObject<GameCamera>();
		}
		//フェードが終了
		else if (!g_fade->IsExecute()) {
			ChengeStage = true;
			Reset();
		}
		break;
		//ゲームオーバー時
	case step_GameOver:
		
		break;
	case step_GameClear:
		
		break;
	}
}
/*!
* @brief	描画。
*/
void GameScene::Render()
{
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	if (finishFadeOut) {
		CoinNum->Draw();
		displayCoin->Render();
	}

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void GameScene::InitSprite()
{
	//スプライトの初期化
	CoinNum = new Sprite();
	CoinNum->Initialize("Assets/sprite/Coin2.png");
	CoinNum->SetPosition(CoinPos);
	CoinNum->SetSize(CoinSize);

	displayCoin = new DisplayCoin;
}

void GameScene::Release()
{
	//delete g_physicsWorld;
	//g_physicsWorld = nullptr;
	map->SetisDead();
	g_player->SetisDead();
	gameCamera->SetisDead();
	delete this;
}

void GameScene::Reset()
{
	//g_player->Reset();
	g_player->SetisDead();
	depthStencilRender->SetisDead();
	//GetGameCamera()->Reset();
	GetGameCamera()->SetisDead();
	map->SetisDead();
}

void GameScene::StageCreate()
{
	int numObject = 0;
	switch (currentStage) {
	case en_Stage1:
		//配置されているオブジェクトの数を計算
		numObject = sizeof(Stage1) / sizeof(Stage1[0]);
		map->Create(Stage1, numObject);
		break;
	case en_Stage2:
		//配置されているオブジェクトの数を計算
		numObject = sizeof(Stage2) / sizeof(Stage2[0]);
		map->Create(Stage2, numObject);
		break;
	}

	step = step_StageLoad;
}
