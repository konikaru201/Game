#include "stdafx.h"
#include "TitleScene.h"
#include "myEngine/system.h"
#include "myEngine/HID/Pad.h"
#include "Fade/Fade.h"
#include "myEngine/Timer/Timer.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "myEngine/Sound/SoundSource.h"

TitleScene* titleScene;

TitleScene::TitleScene(){}
TitleScene::~TitleScene()
{
	delete sprite;
	delete m_pressA;
}

bool TitleScene::Start()
{
	sprite = new Sprite;
	sprite->Initialize("Assets/sprite/Title.png");

	m_pressA = new Sprite;
	m_pressA->Initialize("Assets/sprite/PressA.png");
	m_pressA->SetPosition(D3DXVECTOR2(0.0f, -320.0f));

	g_fade->StartFadeIn();

	return true;
}

void TitleScene::Update()
{
	//Œˆ’è
	if (pad->IsTrigger(pad->enButtonA))
	{
		CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
		SE->Init("Assets/sound/Desision_2.wav");
		SE->Play(false);
		m_changeScene = true;
	}
}

void TitleScene::Render()
{
	sprite->Render();

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pressA->Render();

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}