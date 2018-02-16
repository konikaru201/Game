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
	delete m_triangle;
}

bool GameOverScene::Start()
{
	m_preGameOverPos = { 0.0f, 720.0f };
	m_preTrianglePos = trianglePos;

	m_gameOver = new Sprite;
	m_gameOver->Initialize("Assets/sprite/GameOver.png");
	m_gameOver->SetPosition(m_preGameOverPos);

	m_continue = new Sprite;
	m_continue->Initialize("Assets/sprite/Continue.png");
	m_continue->SetPosition(continuePos);
	m_continue->SetAlpha(m_alpha);

	m_stageSelectReturn = new Sprite;
	m_stageSelectReturn->Initialize("Assets/sprite/StageSelectReturn.png");
	m_stageSelectReturn->SetPosition(stageSelectReturnPos);
	m_stageSelectReturn->SetAlpha(m_alpha);

	m_titleReturn = new Sprite;
	m_titleReturn->Initialize("Assets/sprite/TitleReturn.png");
	m_titleReturn->SetPosition(titleReturnPos);
	m_titleReturn->SetAlpha(m_alpha);

	m_triangle = new Sprite;
	m_triangle->Initialize("Assets/sprite/triangle.png");
	m_triangle->SetPosition(trianglePos);
	m_triangle->SetAlpha(m_alpha);

	//g_fade->StartFadeIn();

	return true;
}

void GameOverScene::Update()
{
	m_gameOverSceneEnd = false;

	//ゲームオーバー文字が表示され終わったか
	if (!m_gameOverSet) {
		float addPos = 5.0f;
		m_preGameOverPos.y -= addPos;
		if (m_preGameOverPos.y <= gameOverPos.y) {
			m_preGameOverPos.y = gameOverPos.y;
			m_gameOverSet = true;
		}
		m_gameOver->SetPosition(m_preGameOverPos);
	}

	if (!m_gameOverSet) { return; }

	m_timer += Timer::GetFrameDeltaTime();
	if (m_timer < FADE_TIME) {
		float t = m_timer / FADE_TIME;
		//透明度
		m_continue->SetAlpha(min(t, 1.0f));
		m_stageSelectReturn->SetAlpha(min(t, 1.0f));
		m_titleReturn->SetAlpha(min(t, 1.0f));
		m_triangle->SetAlpha(min(t, 1.0f));
	}
	else {
		m_continue->SetAlpha(1.0f);
		m_stageSelectReturn->SetAlpha(1.0f);
		m_titleReturn->SetAlpha(1.0f);
		m_triangle->SetAlpha(1.0f);
	}


	//上を選択(続ける、戻る)
	if (pad->IsTrigger(pad->enButtonUp)) {
		if (m_state == state_return || m_state == state_End) {
			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/Select.wav");
			SE->Play(false);

			if (m_state == state_return) {
				m_state = state_Continue;
				m_preTrianglePos.y = continuePos.y;
				m_preTrianglePos.x += 150.0f;
				m_preTrianglePos.y -= 20.0f;
			}
			else {
				m_state = state_return;
				m_preTrianglePos.y = stageSelectReturnPos.y;
				m_preTrianglePos.x -= 150.0f;
				m_preTrianglePos.y -= 20.0f;
			}
			
			m_triangle->SetPosition(m_preTrianglePos);
		}
	}
	//下を選択(戻る、終了)
	else if (pad->IsTrigger(pad->enButtonDown)) {
		if (m_state == state_Continue || m_state == state_return) {
			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/Select.wav");
			SE->Play(false);

			if (m_state == state_Continue) {
				m_state = state_return;
				m_preTrianglePos.y = stageSelectReturnPos.y;
				m_preTrianglePos.x -= 150.0f;
				m_preTrianglePos.y -= 20.0f;
			}
			else {
				m_state = state_End;
				m_preTrianglePos.y = titleReturnPos.y;
				m_preTrianglePos.x += 150.0f;
				m_preTrianglePos.y -= 20.0f;
			}

			m_triangle->SetPosition(m_preTrianglePos);
		}
	}

	//決定
	if (pad->IsTrigger(pad->enButtonA)) {
		CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
		SE->Init("Assets/sound/Desision_2.wav");
		SE->Play(false);
		m_gameOverSceneEnd = true;
	}
}

void GameOverScene::Render()
{
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_gameOver->Render();
	if (m_gameOverSet) {
		m_continue->Render();
		m_stageSelectReturn->Render();
		m_titleReturn->Render();
		m_triangle->Render();
	}
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}