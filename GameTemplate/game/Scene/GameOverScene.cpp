#include "stdafx.h"
#include "GameOverScene.h"
#include "myEngine/system.h"
#include "myEngine/HID/Pad.h"
#include "Fade/Fade.h"
#include "myEngine/Timer/Timer.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "myEngine/Sound/SoundSource.h"

GameOverScene::GameOverScene() {}
GameOverScene::~GameOverScene()
{
	delete m_gameOver;
	delete m_continue;
	delete m_stageSelectReturn;
	delete m_titleReturn;
}

bool GameOverScene::Start()
{
	m_gameOver = new Sprite;
	m_gameOver->Initialize("Assets/sprite/GameOver.png");
	m_gameOver->SetPosition(gameOverPos);

	m_continue = new Sprite;
	m_continue->Initialize("Assets/sprite/Continue.png");
	m_continue->SetPosition(continuePos);

	m_stageSelectReturn = new Sprite;
	m_stageSelectReturn->Initialize("Assets/sprite/StageSelectReturn.png");
	m_stageSelectReturn->SetPosition(stageSelectReturnPos);

	m_titleReturn = new Sprite;
	m_titleReturn->Initialize("Assets/sprite/TitleReturn.png");
	m_titleReturn->SetPosition(titleReturnPos);

	m_triangle = new Sprite;
	m_triangle->Initialize("Assets/sprite/triangle.png");
	m_triangle->SetPosition(trianglePos);

	m_preTrianglePos = trianglePos;

	g_fade->StartFadeIn();

	return true;
}

void GameOverScene::Update()
{
	//上を選択(続ける、戻る)
	if (pad->IsTrigger(pad->enButtonUp)) {
		if (state == state_return || state == state_End) {
			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/Select.wav");
			SE->Play(false);

			if (state == state_return) {
				state = state_Continue;
				m_preTrianglePos.y = continuePos.y;
			}
			else {
				state = state_return;
				m_preTrianglePos.y = stageSelectReturnPos.y;
			}
			
			m_triangle->SetPosition(m_preTrianglePos);
		}
	}
	//下を選択(戻る、終了)
	else if (pad->IsTrigger(pad->enButtonDown)) {
		if (state == state_Continue || state == state_return) {
			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/Select.wav");
			SE->Play(false);

			if (state == state_Continue) {
				state = state_return;
				m_preTrianglePos.y = stageSelectReturnPos.y;
			}
			else {
				state = state_End;
				m_preTrianglePos.y = titleReturnPos.y;
			}

			m_triangle->SetPosition(m_preTrianglePos);
		}
	}

	//決定
	if (pad->IsTrigger(pad->enButtonA)) {
		CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
		SE->Init("Assets/sound/Desision_2.wav");
		SE->Play(false);
		m_changeScene = true;
	}
}

void GameOverScene::Render()
{
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_gameOver->Render();
	m_continue->Render();
	m_stageSelectReturn->Render();
	m_titleReturn->Render();
	m_triangle->Render();

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}