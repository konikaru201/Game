#include "stdafx.h"
#include "Bloom.h"

void Bloom::UpdateWeight(float dispersion)
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

Bloom::Bloom()
{
	//ブルームのシェーダーをロード
	m_effect = g_effectManager->LoadEffect("Assets/Shader/bloom.fx");
	//輝度抽出用のレンダリングターゲットを作成する
	m_luminanceRenderTarget.Create(
		FRAME_BUFFER_WIDTH,
		FRAME_BUFFER_HEIGHT,
		1,
		D3DFMT_A16B16G16R16F,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0
	);

	int w = FRAME_BUFFER_WIDTH;
	int h = FRAME_BUFFER_HEIGHT;
	//MGF用のレンダリングターゲットを作成
	for (int i = 0; i < NUM_DOWN_SAMPLING_COUNT; i++)
	{
		//ブラーをかけるためのダウンサンプリング用のレンダリングターゲットを作成。
		//横ブラー用。
		w /= 2;	//横の解像度をフレームバッファの半分にする。
		m_downSamplingRenderTarget[i][0].Create(
			w,	
			h,
			1,
			D3DFMT_A16B16G16R16F,
			D3DFMT_D16,
			D3DMULTISAMPLE_NONE,
			0
		);
		//縦ブラー用。
		h /= 2;	//縦の解像度を半分にする。
		m_downSamplingRenderTarget[i][1].Create(
			w,	//縦と横の解像度をフレームバッファの半分にする。
			h,
			1,
			D3DFMT_A16B16G16R16F,
			D3DFMT_D16,
			D3DMULTISAMPLE_NONE,
			0
		);
	}
	m_combineRenderTarget.Create(
		w / 2,
		h / 2,
		1,
		D3DFMT_A16B16G16R16F,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0
	);
}

Bloom::~Bloom()
{
}

void Bloom::Render()
{
	//Zテストで失敗したら困るので、Zテストは無効にしておく
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//輝度を抽出する
	{
		//αブレンドもいらない
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		//輝度抽出用のレンダリングターゲットを変更する
		g_pd3dDevice->SetRenderTarget(0, m_luminanceRenderTarget.GetRenderTarget());
		g_pd3dDevice->SetDepthStencilSurface(m_luminanceRenderTarget.GetDepthStencilBuffer());
		//黒でクリア
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		//輝度抽出テクニックをセット
		m_effect->SetTechnique("SamplingLuminance");
		m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_effect->BeginPass(0);
		//シーンテクスチャを設定する。
		m_effect->SetTexture("g_scene", mainRenderTarget->GetTexture());
		//定数レジスタへの変更をコミット。
		m_effect->CommitChanges();
		DrawQuadPrimitive();

		m_effect->EndPass();
		m_effect->End();
	}

	//ガウスブラーで使う重みテーブルを更新。
	UpdateWeight(25.0f);

	//ブラーをかける輝度テクスチャのサイズ。
	int luminanceTexW = m_luminanceRenderTarget.GetWidth();
	int luminanceTexH = m_luminanceRenderTarget.GetHeight();
	LPDIRECT3DTEXTURE9 blurTexture = m_luminanceRenderTarget.GetTexture();
	for (int i = 0; i < NUM_DOWN_SAMPLING_COUNT; i++) 
	{
		//輝度を抽出したテクスチャをXブラー
		//ダウンサンプリング用のレンダリングターゲットを追加。
		g_pd3dDevice->SetRenderTarget(0, m_downSamplingRenderTarget[i][0].GetRenderTarget());
		//横ブラー用のシェーダーテクニックを設定する。
		m_effect->SetTechnique("XBlur");
		m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_effect->BeginPass(0);

		//輝度テクスチャのサイズを転送。
		float size[2];
		size[0] = (float)luminanceTexW;
		size[1] = (float)luminanceTexH;
		m_effect->SetValue("g_luminanceTexSize", size, sizeof(size));

		//オフセットを転送。
		float offset[2];
		offset[0] = 16.0f / size[0];
		offset[1] = 0.0f;
		m_effect->SetValue("g_offset", offset, sizeof(offset));

		//レンダリングターゲットのサイズを転送。
		float renderTargetSize[2];
		renderTargetSize[0] = (float)m_downSamplingRenderTarget[i][0].GetWidth();
		renderTargetSize[1] = (float)m_downSamplingRenderTarget[i][0].GetHeight();
		m_effect->SetValue("g_renderTargetSize", renderTargetSize, sizeof(renderTargetSize));

		m_effect->SetValue("g_weight", m_weights, sizeof(m_weights));

		m_effect->SetTexture("g_blur", blurTexture);
		m_effect->CommitChanges();
		DrawQuadPrimitive();

		m_effect->EndPass();
		m_effect->End();
		

		//輝度を抽出したテクスチャをYブラー

		g_pd3dDevice->SetRenderTarget(0, m_downSamplingRenderTarget[i][1].GetRenderTarget());
		//縦ブラー用のシェーダーテクニックを設定する。
		m_effect->SetTechnique("YBlur");
		m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_effect->BeginPass(0);
		
		blurTexture = m_downSamplingRenderTarget[i][0].GetTexture();
		//輝度テクスチャのサイズを転送。
		size[0] = (float)m_downSamplingRenderTarget[i][0].GetWidth();
		size[1] = (float)m_downSamplingRenderTarget[i][0].GetHeight();
		m_effect->SetValue("g_luminanceTexSize", size, sizeof(size));

		//オフセットを転送。
		offset[0] = 0.0f;
		offset[1] = 16.0f / size[1];
		m_effect->SetValue("g_offset", offset, sizeof(offset));

		//レンダリングターゲットのサイズを転送。
		renderTargetSize[0] = (float)m_downSamplingRenderTarget[i][1].GetWidth();
		renderTargetSize[1] = (float)m_downSamplingRenderTarget[i][1].GetHeight();
		m_effect->SetValue("g_renderTargetSize", renderTargetSize, sizeof(renderTargetSize));

		m_effect->SetValue("g_weight", m_weights, sizeof(m_weights));

		m_effect->SetTexture("g_blur", blurTexture);
		m_effect->CommitChanges();
		DrawQuadPrimitive();

		m_effect->EndPass();
		m_effect->End();
		
		luminanceTexW = m_downSamplingRenderTarget[i][1].GetWidth();
		luminanceTexH = m_downSamplingRenderTarget[i][1].GetHeight();
		blurTexture = m_downSamplingRenderTarget[i][1].GetTexture();

	}

	{
		//ボケフィルターの合成
		g_pd3dDevice->SetRenderTarget(0, m_combineRenderTarget.GetRenderTarget());

		float offset[2];
		offset[0] = 0.5f / m_combineRenderTarget.GetWidth();
		offset[1] = 0.5f / m_combineRenderTarget.GetHeight();

		m_effect->SetTechnique("Combine");
		m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_effect->BeginPass(0);

		m_effect->SetTexture( "g_combineTex00", m_downSamplingRenderTarget[0][0].GetTexture());
		m_effect->SetTexture( "g_combineTex01", m_downSamplingRenderTarget[1][0].GetTexture());
		m_effect->SetTexture( "g_combineTex02", m_downSamplingRenderTarget[2][0].GetTexture());
		m_effect->SetTexture( "g_combineTex03", m_downSamplingRenderTarget[3][0].GetTexture());
		m_effect->SetTexture( "g_combineTex04", m_downSamplingRenderTarget[4][0].GetTexture());
		m_effect->SetValue( "g_offset", offset, sizeof(offset));

		m_effect->CommitChanges();
		DrawQuadPrimitive();

		m_effect->EndPass();
		m_effect->End();
	}


	{
		float offset[2];
		//加算合成
		offset[0] = 0.5f / m_combineRenderTarget.GetWidth();
		offset[1] = 0.5f / m_combineRenderTarget.GetWidth();

		//メインのレンダリングターゲットに戻す。
		g_pd3dDevice->SetRenderTarget(0, mainRenderTarget->GetRenderTarget());
		g_pd3dDevice->SetDepthStencilSurface(mainRenderTarget->GetDepthStencilBuffer());

		//加算合成。
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		m_effect->SetTechnique("Final");
		m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_effect->BeginPass(0);
		m_effect->SetTexture("g_blur", blurTexture);
		m_effect->SetValue("g_offset", offset, sizeof(offset));
		m_effect->CommitChanges();
		DrawQuadPrimitive();

		m_effect->EndPass();
		m_effect->End();

		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	}
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}