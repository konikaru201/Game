#include "stdafx.h"
#include "ResultScene.h"
#include "myEngine/system.h"
#include "myEngine/HID/Pad.h"
#include "../Fade/Fade.h"
#include "../myEngine/Timer/Timer.h"

ResultScene::ResultScene() {}
ResultScene::~ResultScene()
{
	delete sprite;
}

bool ResultScene::Start()
{
	sprite = new Sprite;
	sprite->Initialize("Assets/sprite/GameOver.png");

	g_fade->StartFadeIn();

	return true;
}

void ResultScene::Update()
{
	//Aボタンでシーン切り替えフラグを立てる
	if (pad->IsTrigger(pad->enButtonA)) {
		m_changeScene = true;
	}
}

void ResultScene::Render()
{
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	sprite->Render();

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}