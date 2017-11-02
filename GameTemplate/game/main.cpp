/*!
 *@brief	ゲームテンプレート。
 */
#include "stdafx.h"
#include "Scene/SceneManager.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "myEngine/HID/Pad.h"
#include "Fade/Fade.h"
#include "myEngine/Graphics/RenderTarget.h"
#include "myEngine/Graphics/ShadowMap.h"
#include "Scene/GameScene.h"
#include "Player/Player.h"

GameObjectManager* goMgr = nullptr;
Pad* pad = nullptr;
SceneManager* sceneManager = nullptr;
Fade* g_fade = nullptr;

CShadowMap g_shadowMap;	//シャドウマップ。

//-----------------------------------------------------------------------------
// Name: ゲームを初期化。
//-----------------------------------------------------------------------------
void Init()
{
	g_shadowMap.Init();

	goMgr = new GameObjectManager;

	g_fade = new Fade;
	g_fade->Start();

	pad = goMgr->NewGameObject<Pad>();

	sceneManager = goMgr->NewGameObject<SceneManager>();
}
//-----------------------------------------------------------------------------
// Name: 描画処理。％
//-----------------------------------------------------------------------------
VOID Render()
{
	if (g_player != nullptr) {
		D3DXVECTOR3 target = g_player->GetPosition();
		D3DXVECTOR3 viewPos = target;
		viewPos.y += 4.0f;
		g_shadowMap.SetLightViewPosition(viewPos);
		g_shadowMap.SetLightViewTarget(target);
	}
	else {
		g_shadowMap.SetLightViewPosition(D3DXVECTOR3(0.0f, 10.0f, 0.0f));
		g_shadowMap.SetLightViewTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//if (g_coin != nullptr) {
	//	D3DXVECTOR3 target = g_coin->GetPosition();
	//	D3DXVECTOR3 viewPos = target;
	//	viewPos.y += 10.0f;
	//	g_shadowMap.SetLightViewPosition(viewPos);
	//	g_shadowMap.SetLightViewTarget(target);
	//}
	//else {
	//	g_shadowMap.SetLightViewPosition(D3DXVECTOR3(0.0f, 10.0f, 0.0f));
	//	g_shadowMap.SetLightViewTarget(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}

	g_shadowMap.Update();

	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//シーンの描画開始。
	g_pd3dDevice->BeginScene();

	//シャドウマップにレンダリング。
	g_shadowMap.Draw();

	goMgr->Render();
	if (gameScene != nullptr) {
		gameScene->Render();
	}
	g_fade->Render();

	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

	
}
/*!-----------------------------------------------------------------------------
 *@brief	更新処理。
 -----------------------------------------------------------------------------*/
void Update()
{
	goMgr->Update();
	g_fade->Update();
}
//-----------------------------------------------------------------------------
//ゲームが終了するときに呼ばれる処理。
//-----------------------------------------------------------------------------
void Terminate()
{
	delete goMgr;
	delete g_fade;
	delete g_effectManager;
}

void Delete()
{
	goMgr->DeleteGameObject();
}
