#include "stdafx.h"
#include "Bloom.h"

void Bloom::UpdateWeight(float dispersion)
{
	float total = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		weights[i] = expf(-0.5f*(float)(i*i) / dispersion);
		total += 2.0f*weights[i];
	}
	//�K�i��
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		weights[i] /= total;
	}
}

Bloom::Bloom()
{
	//�u���[���̃V�F�[�_�[�����[�h
	effect = g_effectManager->LoadEffect("Assets/Shader/bloom.fx");
	//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬����
	luminanceRenderTarget.Create(
		FRAME_BUFFER_WIDTH,
		FRAME_BUFFER_HEIGHT,
		1,
		D3DFMT_A16B16G16R16F,
		D3DFMT_D16,
		D3DMULTISAMPLE_NONE,
		0
	);

	//�u���[�������邽�߂̃_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g���쐬�B
	//���u���[�p�B
	downSamplingRenderTarget[0].Create(
		FRAME_BUFFER_WIDTH / 2,	//���̉𑜓x���t���[���o�b�t�@�̔����ɂ���B
		FRAME_BUFFER_HEIGHT,
		1,
		D3DFMT_A16B16G16R16F,	
		D3DFMT_D16,				
		D3DMULTISAMPLE_NONE,	
		0						
	);
	//�c�u���[�p�B
	downSamplingRenderTarget[1].Create(
		FRAME_BUFFER_WIDTH / 2,	//�c�Ɖ��̉𑜓x���t���[���o�b�t�@�̔����ɂ���B
		FRAME_BUFFER_HEIGHT / 2,
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
		g_pd3dDevice->SetRenderTarget(0, luminanceRenderTarget.GetRenderTarget());
		g_pd3dDevice->SetDepthStencilSurface(luminanceRenderTarget.GetDepthStencilBuffer());
		//���ŃN���A
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		//�P�x���o�e�N�j�b�N���Z�b�g
		effect->SetTechnique("SamplingLuminance");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		//�V�[���e�N�X�`����ݒ肷��B
		effect->SetTexture("g_scene", mainRenderTarget->GetTexture());
		//�萔���W�X�^�ւ̕ύX���R�~�b�g�B
		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();
	}

	//�K�E�X�u���[�Ŏg���d�݃e�[�u�����X�V�B
	UpdateWeight(25.0f);

	//�P�x�𒊏o�����e�N�X�`����X�u���[
	{
		//�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g��ǉ��B
		g_pd3dDevice->SetRenderTarget(0, downSamplingRenderTarget[0].GetRenderTarget());
		//���u���[�p�̃V�F�[�_�[�e�N�j�b�N��ݒ肷��B
		effect->SetTechnique("XBlur");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		float size[2] = {
			(float)(luminanceRenderTarget.GetWidth()),
			(float)(luminanceRenderTarget.GetHeight())
		};
		float offset[] = {
			16.0f / (float)(luminanceRenderTarget.GetWidth()),
			0.0f
		};
		effect->SetValue("g_luminanceTexSize", size, sizeof(size));
		effect->SetValue("g_offset", offset, sizeof(size));
		effect->SetValue("g_weight", weights, sizeof(weights));

		effect->SetTexture("g_blur", luminanceRenderTarget.GetTexture());
		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();
	}
	//�P�x�𒊏o�����e�N�X�`����Y�u���[
	{
		//�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g��ǉ��B
		g_pd3dDevice->SetRenderTarget(0, downSamplingRenderTarget[1].GetRenderTarget());
		//�c�u���[�p�̃V�F�[�_�[�e�N�j�b�N��ݒ肷��B
		effect->SetTechnique("YBlur");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		float size[2] = {
			(float)(downSamplingRenderTarget[0].GetWidth()),
			(float)(downSamplingRenderTarget[0].GetHeight())
		};
		float offset[] = {
			0.0f ,
			16.0f / (float)(downSamplingRenderTarget[0].GetHeight())
		};
		effect->SetValue("g_luminanceTexSize", size, sizeof(size));
		effect->SetValue("g_offset", offset, sizeof(size));
		effect->SetValue("g_weight", weights, sizeof(weights));

		effect->SetTexture("g_blur", downSamplingRenderTarget[0].GetTexture());
		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();
	}

	//���C���̃����_�����O�^�[�Q�b�g�ɖ߂��B
	g_pd3dDevice->SetRenderTarget(0, mainRenderTarget->GetRenderTarget());
	g_pd3dDevice->SetDepthStencilSurface(mainRenderTarget->GetDepthStencilBuffer());


	{
		//�ŏI�����B
		float offset[] = {
			0.5f / downSamplingRenderTarget[1].GetWidth() ,
			0.5f / downSamplingRenderTarget[1].GetHeight()
		};

		//���Z�����B
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		effect->SetTechnique("Final");
		effect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		effect->BeginPass(0);
		effect->SetTexture("g_blur", downSamplingRenderTarget[1].GetTexture());
		effect->SetValue("g_offset", offset, sizeof(offset));
		effect->CommitChanges();
		DrawQuadPrimitive();

		effect->EndPass();
		effect->End();

		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
}