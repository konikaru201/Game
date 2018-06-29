#include "stdafx.h"
#include "TitleScene.h"
#include "myEngine/system.h"
#include "myEngine/HID/Pad.h"
#include "Fade/Fade.h"
#include "myEngine/Timer/Timer.h"
#include "myEngine/GameObject/GameObjectManager.h"

TitleScene::TitleScene()
{
	titleBackGround = std::make_unique<TitleBackGround>();
}

TitleScene::~TitleScene()
{
}

bool TitleScene::Start()
{
	titleBackGround->Init();

	m_pressA = std::make_unique<Sprite>();
	m_pressA->Initialize("Assets/sprite/PressA.png");
	m_pressA->SetPosition(D3DXVECTOR2(0.0f, -320.0f));

	m_bgmSource = goMgr->NewGameObject<CSoundSource>();
	m_bgmSource->InitStreaming("Assets/sound/opening.wav");
	m_bgmSource->Play(true);

	g_fade->StartFadeIn();

	return true;
}

void TitleScene::Update()
{
	titleBackGround->Update();

	switch (m_state) {
	case Entity:
		m_timer += Timer::GetFrameDeltaTime();
		if (m_timer < ALPHA_TIME) {
			float t = m_timer / ALPHA_TIME;
			m_pressA->SetAlpha(max(1.0f - t, 0.0f));
		}
		else {
			m_pressA->SetAlpha(0.0f);
			m_state = Clear;
			m_timer = 0.0f;
		}
		break;
	case Clear:
		m_timer += Timer::GetFrameDeltaTime();
		if (m_timer < ALPHA_TIME) {
			float t = m_timer / ALPHA_TIME;
			m_pressA->SetAlpha(min(t, 1.0f));
		}
		else {
			m_pressA->SetAlpha(1.0f);
			m_state = Entity;
			m_timer = 0.0f;
		}
		break;
	}
	

	//Œˆ’è
	if (pad->IsTrigger(pad->enButtonA))
	{
		CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
		SE->Init("Assets/sound/Desision_2.wav");
		SE->Play(false);
		m_changeScene = true;
		m_bgmSource->SetisDead();
	}
}

void TitleScene::Render()
{
	titleBackGround->Render();

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pressA->Render();

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void TitleScene::Release()
{
	titleBackGround->Release();
}
