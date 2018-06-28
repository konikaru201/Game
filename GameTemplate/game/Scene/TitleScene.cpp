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
}

bool TitleScene::Start()
{
	sprite = std::make_unique<Sprite>();
	sprite->Initialize("Assets/sprite/Title.png");

	m_pressA = std::make_unique<Sprite>();
	m_pressA->Initialize("Assets/sprite/PressA.png");
	m_pressA->SetPosition(D3DXVECTOR2(0.0f, -320.0f));

	m_titleName = std::make_unique<Sprite>();
	m_titleName->Initialize("Assets/sprite/TitleName.png");
	m_titleName->SetPosition(D3DXVECTOR2(0.0f, 300.0f));
	m_titleName->SetSize(D3DXVECTOR2(1280.0f, 720.0f));

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
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	sprite->Render();
	m_pressA->Render();
	m_titleName->Render();

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}