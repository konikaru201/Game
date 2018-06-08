#include "stdafx.h"
#include "WipeEffect.h"
#include "myEngine/Timer/Timer.h"

WipeEffect::WipeEffect(){}

WipeEffect::~WipeEffect(){}

bool WipeEffect::Start()
{
	m_circle = new Sprite();
	m_circle->Initialize("Assets/sprite/circle.png");
	m_circle->SetPosition(D3DXVECTOR2(0.0f, 0.0f));
	m_circle->SetSize(D3DXVECTOR2(0.0f, 0.0f));

	m_back = new Sprite();
	m_back->Initialize("Assets/sprite/back.png");
	m_back->SetPosition(D3DXVECTOR2(0.0f, 0.0f));
	m_back->SetAlpha(0.0f);
	return true;
}

void WipeEffect::Update()
{
	if (m_isWipe) {
		switch (m_state)
		{
		case WipeOut:
			if (m_timer < WIPE_TIME) {
				float t = (WIPE_TIME - m_timer) / WIPE_TIME;
				m_circle->SetSize(D3DXVECTOR2(1500 * t, 1500 * t));
			}
			else {
				m_isWipe = false;
			}
			m_timer += Timer::GetFrameDeltaTime();

			break;

		case WipeIn:
			if (m_timer < WIPE_TIME) {
				float t = m_timer / WIPE_TIME;
				m_circle->SetSize(D3DXVECTOR2(1500 * t, 1500 * t));
			}
			else {
				m_isWipe = false;
			}
			m_timer += Timer::GetFrameDeltaTime();

			break;
		}
	}
}

void WipeEffect::Render()
{
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ステンシルバッファだけを0クリアします
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_STENCIL, 0, 1.0f, static_cast<DWORD>(0));

	// ステンシルバッファの設定
	g_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);  // ステンシルバッファ有効
	g_pd3dDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS); // ステンシルテストは常に行う
	g_pd3dDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	g_pd3dDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_REPLACE);
	g_pd3dDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	g_pd3dDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	m_circle->Render();

	g_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_NOTEQUAL);
	g_pd3dDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
	g_pd3dDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	g_pd3dDevice->SetRenderState(D3DRS_STENCILREF, 0x01);
	g_pd3dDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	m_back->Render();

	g_pd3dDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
