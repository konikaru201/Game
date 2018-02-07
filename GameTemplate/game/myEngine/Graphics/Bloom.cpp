#include "stdafx.h"
#include "Bloom.h"

void Bloom::UpdateWeight(float dispersion)
{
	float total = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_weights[i] = expf(-0.5f*(float)(i*i) / dispersion);
		total += 2.0f* m_weights[i];
	}
	//�K�i��
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_weights[i] /= total;
	}
}

Bloom::Bloom()
{
	//�u���[���̃V�F�[�_�[�����[�h
	m_effect = g_effectManager->LoadEffect("Assets/Shader/bloom.fx");
	//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬����
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
	//MGF�p�̃����_�����O�^�[�Q�b�g���쐬
	for (int i = 0; i < NUM_DOWN_SAMPLING_COUNT; i++)
	{
		//�u���[�������邽�߂̃_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g���쐬�B
		//���u���[�p�B
		w /= 2;	//���̉𑜓x���t���[���o�b�t�@�̔����ɂ���B
		m_downSamplingRenderTarget[i][0].Create(
			w,	
			h,
			1,
			D3DFMT_A16B16G16R16F,
			D3DFMT_D16,
			D3DMULTISAMPLE_NONE,
			0
		);
		//�c�u���[�p�B
		h /= 2;	//�c�̉𑜓x�𔼕��ɂ���B
		m_downSamplingRenderTarget[i][1].Create(
			w,	//�c�Ɖ��̉𑜓x���t���[���o�b�t�@�̔����ɂ���B
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
	//Z�e�X�g�Ŏ��s�����獢��̂ŁAZ�e�X�g�͖����ɂ��Ă���
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	//�P�x�𒊏o����
	{
		//���u�����h������Ȃ�
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		//�P�x���o�p�̃����_�����O�^�[�Q�b�g��ύX����
		g_pd3dDevice->SetRenderTarget(0, m_luminanceRenderTarget.GetRenderTarget());
		g_pd3dDevice->SetDepthStencilSurface(m_luminanceRenderTarget.GetDepthStencilBuffer());
		//���ŃN���A
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		//�P�x���o�e�N�j�b�N���Z�b�g
		m_effect->SetTechnique("SamplingLuminance");
		m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_effect->BeginPass(0);
		//�V�[���e�N�X�`����ݒ肷��B
		m_effect->SetTexture("g_scene", mainRenderTarget->GetTexture());
		//�萔���W�X�^�ւ̕ύX���R�~�b�g�B
		m_effect->CommitChanges();
		DrawQuadPrimitive();

		m_effect->EndPass();
		m_effect->End();
	}

	//�K�E�X�u���[�Ŏg���d�݃e�[�u�����X�V�B
	UpdateWeight(25.0f);

	//�u���[��������P�x�e�N�X�`���̃T�C�Y�B
	int luminanceTexW = m_luminanceRenderTarget.GetWidth();
	int luminanceTexH = m_luminanceRenderTarget.GetHeight();
	LPDIRECT3DTEXTURE9 blurTexture = m_luminanceRenderTarget.GetTexture();
	for (int i = 0; i < NUM_DOWN_SAMPLING_COUNT; i++) 
	{
		//�P�x�𒊏o�����e�N�X�`����X�u���[
		//�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g��ǉ��B
		g_pd3dDevice->SetRenderTarget(0, m_downSamplingRenderTarget[i][0].GetRenderTarget());
		//���u���[�p�̃V�F�[�_�[�e�N�j�b�N��ݒ肷��B
		m_effect->SetTechnique("XBlur");
		m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_effect->BeginPass(0);

		//�P�x�e�N�X�`���̃T�C�Y��]���B
		float size[2];
		size[0] = (float)luminanceTexW;
		size[1] = (float)luminanceTexH;
		m_effect->SetValue("g_luminanceTexSize", size, sizeof(size));

		//�I�t�Z�b�g��]���B
		float offset[2];
		offset[0] = 16.0f / size[0];
		offset[1] = 0.0f;
		m_effect->SetValue("g_offset", offset, sizeof(offset));

		//�����_�����O�^�[�Q�b�g�̃T�C�Y��]���B
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
		

		//�P�x�𒊏o�����e�N�X�`����Y�u���[

		g_pd3dDevice->SetRenderTarget(0, m_downSamplingRenderTarget[i][1].GetRenderTarget());
		//�c�u���[�p�̃V�F�[�_�[�e�N�j�b�N��ݒ肷��B
		m_effect->SetTechnique("YBlur");
		m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_effect->BeginPass(0);
		
		blurTexture = m_downSamplingRenderTarget[i][0].GetTexture();
		//�P�x�e�N�X�`���̃T�C�Y��]���B
		size[0] = (float)m_downSamplingRenderTarget[i][0].GetWidth();
		size[1] = (float)m_downSamplingRenderTarget[i][0].GetHeight();
		m_effect->SetValue("g_luminanceTexSize", size, sizeof(size));

		//�I�t�Z�b�g��]���B
		offset[0] = 0.0f;
		offset[1] = 16.0f / size[1];
		m_effect->SetValue("g_offset", offset, sizeof(offset));

		//�����_�����O�^�[�Q�b�g�̃T�C�Y��]���B
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
		//�{�P�t�B���^�[�̍���
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
		//���Z����
		offset[0] = 0.5f / m_combineRenderTarget.GetWidth();
		offset[1] = 0.5f / m_combineRenderTarget.GetWidth();

		//���C���̃����_�����O�^�[�Q�b�g�ɖ߂��B
		g_pd3dDevice->SetRenderTarget(0, mainRenderTarget->GetRenderTarget());
		g_pd3dDevice->SetDepthStencilSurface(mainRenderTarget->GetDepthStencilBuffer());

		//���Z�����B
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