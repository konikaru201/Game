#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

class Star : public GameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	Star();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~Star();
	/*!
	*@brief	������
	* @param[in]	pos		���W
	* @param[in]	rot		��]
	*/
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);
	/*!
	*@brief	�X�V
	*/
	void Update();
	/*!
	*@brief	�`��
	*/
	void Render();
	/*!
	* @brief	�e��`��
	* @param[in]	viewMatrix		�r���[�s��
	* @param[in]	projMatrix		�v���W�F�N�V�����s��
	* @param[in]	isDrawShadowMap	�V���h�E�}�b�v��`���t���O
	* @param[in]	isRecieveShadow	�V���h�E���V�[�o�[���ǂ���
	*/
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);
	/*!
	* @brief	�v���C���[�̍��W�̎擾
	*@return	�v���C���[�̍��W
	*/
	const D3DXVECTOR3& GetPosition() const
	{
		return m_position;
	}
	/*!
	*@brief	�X�^�[�l���t���O���擾
	*/
	bool GetStar() const
	{
		return m_flag;
	}
private:
	SkinModel		m_model;			//�X�L�����f��
	SkinModelData	m_modelData;		//�X�L�����f���f�[�^
	Light			m_light;			//���C�g
	D3DXVECTOR3		m_position;			//���W
	D3DXQUATERNION	m_rotation;			//��]
	D3DXVECTOR3		m_initPosition;		//�������W
	bool			m_flag = false;		//�X�^�[�l���t���O
	float			m_moveSpeed = 0.05f;//�ړ����x
	float			m_timer = 0.0f;		//�^�C�}�[
};