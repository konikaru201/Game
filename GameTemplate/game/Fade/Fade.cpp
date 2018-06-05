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
	m_sprite = new Sprite();
	m_sprite->Initialize("Assets/sprite/Loading.png");

	m_sprite->SetAlpha(0.0f);

	return true;
}

void Fade::Update()
{
	if (m_isExecute) {
		switch (m_state) {
			//�t�F�[�h�A�E�g��
		case FadeOut:
			m_timer += Timer::GetFrameDeltaTime();
			if (m_timer < FADE_TIME) {
				float t = m_timer / FADE_TIME;
				//�����x
				m_sprite->SetAlpha(min(t, 1.0f));
			}
			else {
				m_isExecute = false;
				m_sprite->SetAlpha(1.0f);
			}
			break;

			//�t�F�[�h�C����
		case FadeIn:
			m_timer += Timer::GetFrameDeltaTime();
			if (m_timer < FADE_TIME) {
				float t = m_timer / FADE_TIME;
				m_sprite->SetAlpha(max(1.0f - t, 0.0f));
			}
			else {
				//�����ɂȂ����̂Ŕ�A�N�e�B�u�ɂ���
				m_sprite->SetAlpha(0.0f);
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

	m_sprite->Render();

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}