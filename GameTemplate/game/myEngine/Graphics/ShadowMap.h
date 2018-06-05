/*!
*@brief	�V���h�E�}�b�v�N���X
*/
#pragma once
#include "RenderTarget.h"

class CShadowMap {
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	CShadowMap();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~CShadowMap();
	/*!
	*@brief	�e�N�X�`�����擾
	*@param[in]		number		�ԍ�
	*@return	�e�N�X�`��
	*/
	LPDIRECT3DTEXTURE9 GetTexture(int number)
	{
		return m_renderTarget[number].GetTexture();
	}
	/*!
	*@brief	������
	*/
	void Init();
	/*!
	*@brief	���C�g�r���[�̎��_��ݒ�
	*@param[in]		lightViewPosition		���C�g�r���[�̎��_
	*/
	void SetLightViewPosition(const D3DXVECTOR3& lightViewPosition)
	{
		m_viewPosition = lightViewPosition;
	}
	/*!
	*@brief	���C�g�r���[�̒����_��ݒ�
	*@param[in]		lightViewTarget		���C�g�r���[�̒����_
	*/
	void SetLightViewTarget(const D3DXVECTOR3& lightViewTarget)
	{
		m_viewTarget = lightViewTarget;
	}
	/*!
	*@brief	���C�g�r���[�s����擾
	*@param[in]		number		�ԍ�
	*@return	���C�g�r���[�s��
	*/
	const D3DXMATRIX& GetLightViewMatrix(int number)
	{
		return m_lightViewMatrix[number];
	}
	/*!
	*@brief	���C�g�v���W�F�N�V�����s����擾
	*@param[in]		number		�ԍ�
	*@return	���C�g�v���W�F�N�V�����s��
	*/
	const D3DXMATRIX& GetLightProjectionMatrix(int number)
	{
		return m_lightProjMatrix[number];
	}
	/*!
	*@brief	���C�g�r���[�v���W�F�N�V�����s����擾
	*@param[in]		number		�ԍ�
	*@return	���C�g�r���[�v���W�F�N�V�����s��
	*/
	const D3DXMATRIX& GetLightViewProjectionMatrix(int number)
	{
		return m_LVPMatrix[number];
	}
	/*!
	*@brief	�X�V
	*/
	void Update();
	/*!
	*@brief	�V���h�E�}�b�v�ɏ�������
	*/
	void Draw();
private:
	static const int	NUM_SHADOW_MAP = 3;					//�V���h�E�}�b�v����鐔�B
	CRenderTarget		m_renderTarget[NUM_SHADOW_MAP];		//�V���h�E�}�b�v���������ރ����_�����O�^�[�Q�b�g�B
	D3DXMATRIX			m_lightViewMatrix[NUM_SHADOW_MAP];	//���C�g�r���[�}�g���N�X�B
	D3DXMATRIX			m_lightProjMatrix[NUM_SHADOW_MAP];	//���C�g�v���W�F�N�V�����}�g���N�X�B
	D3DXMATRIX			m_LVPMatrix[NUM_SHADOW_MAP];		//���C�g�r���[�v���W�F�N�V�����s��B
	D3DXVECTOR3			m_viewPosition;						//���C�g�r���[�̎��_�B
	D3DXVECTOR3			m_viewTarget;						//���C�g�r���[�̒����_�B
	D3DXVECTOR3			m_lightDirection;					//���C�g�̕���
	float				m_lightHeight = 1.0f;				//���C�g�̍���
};

extern CShadowMap g_shadowMap;