#include "stdafx.h"
#include "DepthOfField.h"
#include "myEngine/GameObject/GameObjectManager.h"

DepthOfField::DepthOfField()
{
	//シェーダーをロード
	m_effect = g_effectManager->LoadEffect("Assets/Shader/depthOfField.fx");
	//深度値を書き込むレンダリングターゲットを作成
	m_depthValueRenderTarget.Create(
		FRAME_BUFFER_WIDTH,
		FRAME_BUFFER_HEIGHT,
		1,
		D3DFMT_A16B16G16R16F,
		D3DFMT_D24S8,
		D3DMULTISAMPLE_NONE,
		0
	);

	for (int i = 0; i < 2; i++) {
		//縦と横にブラーをかけるレンダリングターゲットを作成
		//少しぼかしたものと大きくぼかしたもの
		int w = FRAME_BUFFER_WIDTH;
		int h = FRAME_BUFFER_HEIGHT;
		m_blurRenderTarget[i][0].Create(
			w / 2,
			h,
			1,
			D3DFMT_A16B16G16R16F,
			D3DFMT_D16,
			D3DMULTISAMPLE_NONE,
			0
		);
		m_blurRenderTarget[i][1].Create(
			w / 2,
			h / 2,
			1,
			D3DFMT_A16B16G16R16F,
			D3DFMT_D16,
			D3DMULTISAMPLE_NONE,
			0
		);

		//合成用のレンダリングターゲットを作成
		m_combineRenderTarget[i].Create(
			w / 2,
			h / 2,
			1,
			D3DFMT_A16B16G16R16F,
			D3DFMT_D16,
			D3DMULTISAMPLE_NONE,
			0
		);
	}
}

DepthOfField::~DepthOfField()
{
}

void DepthOfField::Render()
{
	if (!m_isDepthOfField) {
		//被写界深度をしないなら何もしない
		return;
	}

	//Zテストで失敗したら困るので、Zテストは無効にしておく
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	//深度値を抽出する
	{
		g_pd3dDevice->SetRenderTarget(0, m_depthValueRenderTarget.GetRenderTarget());
		g_pd3dDevice->SetDepthStencilSurface(m_depthValueRenderTarget.GetDepthStencilBuffer());
		//黒でクリア
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		//深度値を描画
		goMgr->RenderDepthValue();
	}

	for (int i = 0; i < 2; i++) {
		if (i == 0) {
			UpdateWeight(2.0f);
		}
		else {
			UpdateWeight(25.0f);
		}

		//ブラーをかけるテクスチャのサイズ。
		int texW = mainRenderTarget->GetWidth();
		int texH = mainRenderTarget->GetHeight();
		LPDIRECT3DTEXTURE9 blurTexture = mainRenderTarget->GetTexture();
		{
			//テクスチャをXブラー
			g_pd3dDevice->SetRenderTarget(0, m_blurRenderTarget[i][0].GetRenderTarget());
			//横ブラー用のシェーダーテクニックを設定する。
			m_effect->SetTechnique("XBlur");
			m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_effect->BeginPass(0);
			//テクスチャのサイズを転送。
			float size[2];
			size[0] = (float)texW;
			size[1] = (float)texH;
			m_effect->SetValue("g_texSize", size, sizeof(size));
			//オフセットを転送。
			float offset[2];
			offset[0] = 16.0f / size[0];
			offset[1] = 0.0f;
			m_effect->SetValue("g_offset", offset, sizeof(offset));
			//重みを転送。
			m_effect->SetValue("g_weight", m_weights, sizeof(m_weights));
			//テクスチャを転送。
			m_effect->SetTexture("g_blur", blurTexture);
			m_effect->CommitChanges();
			DrawQuadPrimitive();

			m_effect->EndPass();
			m_effect->End();

			//テクスチャをYブラー
			g_pd3dDevice->SetRenderTarget(0, m_blurRenderTarget[i][1].GetRenderTarget());
			//縦ブラー用のシェーダーテクニックを設定する。
			m_effect->SetTechnique("YBlur");
			m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_effect->BeginPass(0);

			blurTexture = m_blurRenderTarget[i][0].GetTexture();
			//輝度テクスチャのサイズを転送。
			size[0] = (float)m_blurRenderTarget[i][0].GetWidth();
			size[1] = (float)m_blurRenderTarget[i][0].GetHeight();
			m_effect->SetValue("g_texSize", size, sizeof(size));
			//オフセットを転送。
			offset[0] = 0.0f;
			offset[1] = 16.0f / size[1];
			m_effect->SetValue("g_offset", offset, sizeof(offset));
			//重みを転送。
			m_effect->SetValue("g_weight", m_weights, sizeof(m_weights));
			//テクスチャを転送。
			m_effect->SetTexture("g_blur", blurTexture);
			m_effect->CommitChanges();
			DrawQuadPrimitive();

			m_effect->EndPass();
			m_effect->End();

			blurTexture = m_blurRenderTarget[i][1].GetTexture();
		}

		{
			//ボケフィルターの合成
			g_pd3dDevice->SetRenderTarget(0, m_combineRenderTarget[i].GetRenderTarget());

			float offset[2];
			offset[0] = 0.0f / m_combineRenderTarget[i].GetWidth();
			offset[1] = 0.0f / m_combineRenderTarget[i].GetHeight();

			m_effect->SetTechnique("Combine");
			m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_effect->BeginPass(0);

			m_effect->SetTexture("g_combineTex00", m_blurRenderTarget[i][0].GetTexture());
			m_effect->SetTexture("g_combineTex01", m_blurRenderTarget[i][1].GetTexture());
			m_effect->SetValue("g_offset", offset, sizeof(offset));

			m_effect->CommitChanges();
			DrawQuadPrimitive();

			m_effect->EndPass();
			m_effect->End();
		}
	}

	{
		float offset[2];
		offset[0] = 0.5f / (FRAME_BUFFER_HEIGHT / 2);
		offset[1] = 0.5f / (FRAME_BUFFER_WIDTH / 2);

		//メインのレンダリングターゲットに戻す。
		g_pd3dDevice->SetRenderTarget(0, mainRenderTarget->GetRenderTarget());
		g_pd3dDevice->SetDepthStencilSurface(mainRenderTarget->GetDepthStencilBuffer());

		m_effect->SetTechnique("Final");
		m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_effect->BeginPass(0);
		m_effect->SetTexture("g_blurTexture0", m_combineRenderTarget[0].GetTexture());
		m_effect->SetTexture("g_blurTexture1", m_combineRenderTarget[1].GetTexture());
		m_effect->SetTexture("g_mainTexture", mainRenderTarget->GetTexture());
		m_effect->SetTexture("g_depthMapTexture", m_depthValueRenderTarget.GetTexture());
		m_effect->SetValue("g_offset", offset, sizeof(offset));
		m_effect->CommitChanges();
		DrawQuadPrimitive();

		m_effect->EndPass();
		m_effect->End();
	}

	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}

void DepthOfField::UpdateWeight(float dispersion)
{
	float total = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_weights[i] = expf(-0.5f*(float)(i*i) / dispersion);
		total += 2.0f* m_weights[i];
	}
	//規格化
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_weights[i] /= total;
	}
}
