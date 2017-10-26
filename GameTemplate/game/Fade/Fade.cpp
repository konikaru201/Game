#include "stdafx.h"
#include "Fade.h"
#include "myEngine/Timer/Timer.h"

namespace {
	const D3DXVECTOR2 BackSize = { 1.0f,1.0f };
	const D3DXVECTOR2 BackPos = { FRAME_BUFFER_WIDTH / 2, FRAME_BUFFER_HEIGHT / 2 };
}

Fade::Fade(){}
Fade::~Fade(){}

bool Fade::Start()
{
	sprite = new Sprite();
	sprite->Initialize("Assets/sprite/loding.png");

	sprite->SetAlpha(0.0f);

	return true;
}

void Fade::Update()
{
	if (m_isExecute) {
		switch (m_state) {
			//フェードアウト中
		case FadeOut:
			m_timer += Timer::GetFrameDeltaTime();
			if (m_timer < FADE_TIME) {
				float t = m_timer / FADE_TIME;
				//透明度
				sprite->SetAlpha(min(t, 1.0f));
			}
			else {
				m_isExecute = false;
				sprite->SetAlpha(1.0f);
			}
			break;

			//フェードイン中
		case FadeIn:
			m_timer += Timer::GetFrameDeltaTime();
			if (m_timer < FADE_TIME) {
				float t = m_timer / FADE_TIME;
				sprite->SetAlpha(max(1.0f - t, 0.0f));
			}
			else {
				//透明になったので非アクティブにする
				sprite->SetAlpha(0.0f);
				m_timer = FADE_TIME;
				m_isExecute = false;
			}
			break;
		}
	}
}

void Fade::Render()
{
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	sprite->Draw();

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}