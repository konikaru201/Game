#include "stdafx.h"
#include "DepthOfField.h"
#include "myEngine/GameObject/GameObjectManager.h"

DepthOfField::DepthOfField()
{
	//�V�F�[�_�[�����[�h
	m_effect = g_effectManager->LoadEffect("Assets/Shader/depthOfField.fx");
	//�[�x�l���������ރ����_�����O�^�[�Q�b�g���쐬
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
		//�c�Ɖ��Ƀu���[�������郌���_�����O�^�[�Q�b�g���쐬
		//�����ڂ��������̂Ƒ傫���ڂ���������
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

		//�����p�̃����_�����O�^�[�Q�b�g���쐬
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
		//��ʊE�[�x�����Ȃ��Ȃ牽�����Ȃ�
		return;
	}

	//Z�e�X�g�Ŏ��s�����獢��̂ŁAZ�e�X�g�͖����ɂ��Ă���
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	//�[�x�l�𒊏o����
	{
		g_pd3dDevice->SetRenderTarget(0, m_depthValueRenderTarget.GetRenderTarget());
		g_pd3dDevice->SetDepthStencilSurface(m_depthValueRenderTarget.GetDepthStencilBuffer());
		//���ŃN���A
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		//�[�x�l��`��
		goMgr->RenderDepthValue();
	}

	for (int i = 0; i < 2; i++) {
		if (i == 0) {
			UpdateWeight(2.0f);
		}
		else {
			UpdateWeight(25.0f);
		}

		//�u���[��������e�N�X�`���̃T�C�Y�B
		int texW = mainRenderTarget->GetWidth();
		int texH = mainRenderTarget->GetHeight();
		LPDIRECT3DTEXTURE9 blurTexture = mainRenderTarget->GetTexture();
		{
			//�e�N�X�`����X�u���[
			g_pd3dDevice->SetRenderTarget(0, m_blurRenderTarget[i][0].GetRenderTarget());
			//���u���[�p�̃V�F�[�_�[�e�N�j�b�N��ݒ肷��B
			m_effect->SetTechnique("XBlur");
			m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_effect->BeginPass(0);
			//�e�N�X�`���̃T�C�Y��]���B
			float size[2];
			size[0] = (float)texW;
			size[1] = (float)texH;
			m_effect->SetValue("g_texSize", size, sizeof(size));
			//�I�t�Z�b�g��]���B
			float offset[2];
			offset[0] = 16.0f / size[0];
			offset[1] = 0.0f;
			m_effect->SetValue("g_offset", offset, sizeof(offset));
			//�d�݂�]���B
			m_effect->SetValue("g_weight", m_weights, sizeof(m_weights));
			//�e�N�X�`����]���B
			m_effect->SetTexture("g_blur", blurTexture);
			m_effect->CommitChanges();
			DrawQuadPrimitive();

			m_effect->EndPass();
			m_effect->End();

			//�e�N�X�`����Y�u���[
			g_pd3dDevice->SetRenderTarget(0, m_blurRenderTarget[i][1].GetRenderTarget());
			//�c�u���[�p�̃V�F�[�_�[�e�N�j�b�N��ݒ肷��B
			m_effect->SetTechnique("YBlur");
			m_effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
			m_effect->BeginPass(0);

			blurTexture = m_blurRenderTarget[i][0].GetTexture();
			//�P�x�e�N�X�`���̃T�C�Y��]���B
			size[0] = (float)m_blurRenderTarget[i][0].GetWidth();
			size[1] = (float)m_blurRenderTarget[i][0].GetHeight();
			m_effect->SetValue("g_texSize", size, sizeof(size));
			//�I�t�Z�b�g��]���B
			offset[0] = 0.0f;
			offset[1] = 16.0f / size[1];
			m_effect->SetValue("g_offset", offset, sizeof(offset));
			//�d�݂�]���B
			m_effect->SetValue("g_weight", m_weights, sizeof(m_weights));
			//�e�N�X�`����]���B
			m_effect->SetTexture("g_blur", blurTexture);
			m_effect->CommitChanges();
			DrawQuadPrimitive();

			m_effect->EndPass();
			m_effect->End();

			blurTexture = m_blurRenderTarget[i][1].GetTexture();
		}

		{
			//�{�P�t�B���^�[�̍���
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

		//���C���̃����_�����O�^�[�Q�b�g�ɖ߂��B
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
	//�K�i��
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_weights[i] /= total;
	}
}
