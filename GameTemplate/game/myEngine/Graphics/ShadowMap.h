#pragma once
#include "RenderTarget.h"

//�V���h�E�}�b�v�N���X�B
class CShadowMap {
public:
	//�R���X�g���N�^
	CShadowMap();

	//�f�X�g���N�^
	~CShadowMap();

	//�e�N�X�`�����擾�B
	LPDIRECT3DTEXTURE9 GetTexture(int number)
	{
		return renderTarget[number].GetTexture();
	}

	//�������B
	void Init();

	//���C�g�r���[�̎��_��ݒ�B
	void SetLightViewPosition(const D3DXVECTOR3& lightViewPosition)
	{
		viewPosition = lightViewPosition;
	}

	//���C�g�r���[�̒����_��ݒ�B
	void SetLightViewTarget(const D3DXVECTOR3& lightViewTarget)
	{
		viewTarget = lightViewTarget;
	}

	//���C�g�r���[�s����擾�B
	const D3DXMATRIX& GetLightViewMatrix(int number)
	{
		return lightViewMatrix[number];
	}

	//���C�g�v���W�F�N�V�����s����擾�B
	const D3DXMATRIX& GetLightProjectionMatrix(int number)
	{
		return lightProjMatrix[number];
	}

	//���C�g�r���[�v���W�F�N�V�����s����擾
	const D3DXMATRIX& GetLightViewProjectionMatrix(int number)
	{
		return m_LVPMatrix[number];
	}

	//�X�V�B
	void Update();

	//�V���h�E�}�b�v�ɏ������݁B
	void Draw();
private:
	static const int NUM_SHADOW_MAP = 3;			//�V���h�E�}�b�v����鐔�B
	CRenderTarget renderTarget[NUM_SHADOW_MAP];		//�V���h�E�}�b�v���������ރ����_�����O�^�[�Q�b�g�B
	D3DXMATRIX  lightViewMatrix[NUM_SHADOW_MAP];	//���C�g�r���[�}�g���N�X�B
	D3DXMATRIX	lightProjMatrix[NUM_SHADOW_MAP];	//���C�g�v���W�F�N�V�����}�g���N�X�B
	D3DXMATRIX  m_LVPMatrix[NUM_SHADOW_MAP];		//���C�g�r���[�v���W�F�N�V�����s��B
	D3DXVECTOR3 viewPosition;						//���C�g�r���[�̎��_�B
	D3DXVECTOR3 viewTarget;							//���C�g�r���[�̒����_�B
	D3DXVECTOR3 m_lightDirection;					//���C�g�̕���
	float		m_lightHeight = 1.0f;				//���C�g�̍���
};

extern CShadowMap g_shadowMap;