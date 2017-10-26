/*!
 * @brief	ゲーム
 */
#include "stdafx.h"
#include "game.h"

SMapInfo mapLocInfo[] = {
#include "Map/locationinfo.h"
};

/*!
 * @brief	コンストラクタ。
 */
Game::Game()
{
}
/*!
 * @brief	デストラクタ。
 */
Game::~Game()
{
	delete g_physicsWorld;
	g_physicsWorld = NULL;
	delete gameCamera;
	gameCamera = NULL;
	delete player;
	player = NULL;
	delete map;
	map = NULL;
	delete pad;
	pad = NULL;
}
/*!
 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
 */
bool Game::Start()
{
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

	goMgr = new GameObjectManager;

	g_physicsWorld = new PhysicsWorld;
	g_physicsWorld->Init();

	titleScene = new TitleScene;
	gameCamera = new GameCamera;	//カメラ生成
	player = new Player;	//プレイヤー生成
	map = new Map;		//マップ生成
	pad = new Pad;

	titleScene->Initialize();

	//ゲームオブジェクトに登録
	goMgr->AddGameObject(titleScene);
	goMgr->AddGameObject(gameCamera);
	goMgr->AddGameObject(player);
	goMgr->AddGameObject(map);
	goMgr->AddGameObject(pad);

	//配置されているオブジェクトの数を計算
	int numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
	map->Create(mapLocInfo, numObject);

	return true;
}
/*!
 * @brief	更新。
 */
void Game::Update()
{
	goMgr->Update();
}
/*!
 * @brief	描画。
 */
void Game::Render()
{
	goMgr->Render();
}
