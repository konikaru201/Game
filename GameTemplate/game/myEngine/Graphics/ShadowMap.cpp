#include "stdafx.h"
#include "ShadowMap.h"
#include "Player/Player.h"
#include "Camera/GameCamera.h"
#include "../GameObject/GameObjectManager.h"

CShadowMap::CShadowMap()
{
	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		D3DXMatrixIdentity(&m_lightViewMatrix[i]);
		D3DXMatrixIdentity(&m_lightProjMatrix[i]);
	}
	m_viewPosition = { 0.0f,0.0f,0.0f };
	m_viewTarget = { 0.0f,0.0f,0.0f };
	m_lightDirection = { 0.0f,-1.0f,0.0f };
}
CShadowMap::~CShadowMap()
{
}

//�������B
void CShadowMap::Init()
{
	int w = 2048;	//��
	int h = 2048;	//����
	//�����_�����O�^�[�Q�b�g���������B
	for (int i = 0; i < 3; i++) {
		m_renderTarget[i].Create(
			w,
			h,
			1,						
			D3DFMT_R32F,			
			D3DFMT_D16,				
			D3DMULTISAMPLE_NONE,	
			0						
		);

		w /= 2;
		h /= 2;
	}
}


//�X�V�B
void CShadowMap::Update()
{
	//�J�����̑O�������擾
	D3DXVECTOR3 cameraDirXZ = gameCamera->GetForward();
	cameraDirXZ.y = 0.0f;
	D3DXVec3Normalize(&cameraDirXZ, &cameraDirXZ);

	//�e�𗎂Ƃ��͈͂�ݒ�
	float shadowAreaTable[] = {
		20.0f,
		40.0f,
		80.0f
	};

	D3DXVECTOR3 lightPos;	//���C�g�̍��W
	float nearPlaneZ = 0.0f;	//�ߕ��ʂ܂ł̋���
	float farPlaneZ;			//�����ʂ܂ł̋���
	D3DXVECTOR3 cameraUp;		//�J�����̏����
	D3DXVec3Cross(&cameraUp, &gameCamera->GetRight(), &gameCamera->GetForward());
	//���C�g�̃r���[�v���W�F�N�V�����s����V���h�E�}�b�v�̖������v�Z����B
	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		farPlaneZ = nearPlaneZ + shadowAreaTable[i];
		//��p�̔������v�Z
		float halfViewAngle = gameCamera->GetAngle() * 0.5f;
		//�������8���_�����C�g��Ԃɕϊ�����AABB�����߂āA���ˉe�̕��ƍ��������߂�B
		float w, h;		//���s���e���镝�ƍ���
		D3DXVECTOR3 v[8];	//8���_�̍��W
		{
			float t = tan(halfViewAngle);
			//�ߕ��ʂƉ����ʂ̒��S���W����[�܂ł̃x�N�g�����v�Z�B
			D3DXVECTOR3 toUpperNear, toUpperFar;
			toUpperNear = cameraUp * t * nearPlaneZ;
			toUpperFar = cameraUp * t * farPlaneZ;
			t *= gameCamera->GetAspect();
			//�ߕ��ʂ̒��S���W���v�Z�B
			D3DXVECTOR3 vWk = gameCamera->GetPosition() + cameraDirXZ * nearPlaneZ;
			lightPos = vWk;
			v[0] = vWk + gameCamera->GetRight() * t * nearPlaneZ + toUpperNear;
			v[1] = v[0] - toUpperNear * 2.0f;

			v[2] = vWk + gameCamera->GetRight() * -t * nearPlaneZ + toUpperNear;
			v[3] = v[2] - toUpperNear * 2.0f;

			//�����ʂ̒��S���W���v�Z�B
			vWk = gameCamera->GetPosition() + cameraDirXZ * farPlaneZ;
			lightPos += vWk;
			v[4] = vWk + gameCamera->GetRight() * t * farPlaneZ + toUpperFar;
			v[5] = v[4] - toUpperFar * 2.0f;

			v[6] = vWk + gameCamera->GetRight() * -t * farPlaneZ + toUpperFar;
			v[7] = v[6] - toUpperFar * 2.0f;

			//���C�g�̍��W���v�Z�B
			lightPos *= 0.5f;
			lightPos += m_lightDirection * -m_lightHeight;

			//���C�g�̒����_���v�Z�B
			D3DXVECTOR3 lightTarget = lightPos;
			lightTarget.y = -50.0f;

			//���C�g�r���[�s����v�Z�B
			D3DXMatrixLookAtLH(&m_lightViewMatrix[i], &lightPos, &lightTarget, &cameraDirXZ);

			//��������\������8���_���v�Z�ł����̂ŁA���C�g��Ԃɍ��W�ϊ����āAAABB�����߂�B
			D3DXVECTOR3 vMax = { -FLT_MAX , -FLT_MAX , -FLT_MAX };
			D3DXVECTOR3 vMin = {  FLT_MAX ,  FLT_MAX ,  FLT_MAX };
			for (auto& vInLight : v) {
				//���[���h��Ԃ̍��W���烉�C�g��Ԃ̍��W�ɕϊ�
				D3DXVec3TransformCoord(&vInLight, &vInLight, &m_lightViewMatrix[i]);
				D3DXVec3Maximize(&vMax, &vMax, &vInLight);
				D3DXVec3Minimize(&vMin, &vMin, &vInLight);
			}
			w = vMax.x - vMin.x;
			h = vMax.y - vMin.y;
		}

		//�v���W�F�N�V�����s����v�Z�B
		D3DXMatrixOrthoLH(
			&m_lightProjMatrix[i],
			w,
			h,
			0.1f,
			1000.0f
		);

		//���C�g�r���[�v���W�F�N�V�����s����쐬�B
		D3DXMatrixMultiply(&m_LVPMatrix[i], &m_lightViewMatrix[i], &m_lightProjMatrix[i]);

		//�ߕ��ʂ��X�V
		nearPlaneZ = farPlaneZ;
	}
}
//�V���h�E�}�b�v�ɏ������݁B
void CShadowMap::Draw()
{
	LPDIRECT3DSURFACE9 renderTargetBackup;
	LPDIRECT3DSURFACE9 depthBufferBackup;
	g_pd3dDevice->GetRenderTarget(0, &renderTargetBackup);		//���X�̃����_�����O�^�[�Q�b�g��ۑ��B��Ŗ߂��K�v������̂ŁB
	g_pd3dDevice->GetDepthStencilSurface(&depthBufferBackup);	//���X�̃f�v�X�X�e���V���o�b�t�@��ۑ��B��Ŗ߂��K�v������̂ŁB

	for (int i = 0; i < NUM_SHADOW_MAP; i++) {
		//�����_�����O�^�[�Q�b�g��ύX����B
		g_pd3dDevice->SetRenderTarget(0, m_renderTarget[i].GetRenderTarget());
		g_pd3dDevice->SetDepthStencilSurface(m_renderTarget[i].GetDepthStencilBuffer());
		//�������ݐ��ύX�����̂ŃN���A�B
		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

		goMgr->RenderToShadow(&m_lightViewMatrix[i], &m_lightProjMatrix[i], true, false);
	}
	g_pd3dDevice->SetRenderTarget(0, renderTargetBackup);		//�߂��B
	g_pd3dDevice->SetDepthStencilSurface(depthBufferBackup);	//�߂��B
}
