/*!
*@brief	�L���[�N���X
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"
#include "myEngine/Graphics/ParticleEmitter.h"
#include "myEngine/Physics/RigidBody.h"

class Killer : public GameObject {
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	Killer();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~Killer();
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
	*@brief	�ړ����x���v�Z
	*@return �ړ����x
	*/
	D3DXVECTOR3 Move();
	/*!
	*@brief	�v���C���[�Ƃ̓����蔻��
	* @param[in]	Length		����
	* @param[in]	toPlayer	�v���C���[�ւ̃x�N�g��
	*/
	void CollisionDetection(float length , const D3DXVECTOR3& toPlayer);
	/*!
	* @brief	�e��`��
	* @param[in]	viewMatrix		�r���[�s��
	* @param[in]	projMatrix		�v���W�F�N�V�����s��
	* @param[in]	isDrawShadowMap	�V���h�E�}�b�v��`���t���O
	* @param[in]	isRecieveShadow	�V���h�E���V�[�o�[���ǂ���
	*/
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);
	/*!
	* @brief	�L���[�̌������擾
	*@return	�L���[�̌���
	*/
	D3DXVECTOR3 GetDirection()
	{
		D3DXMATRIX matrix = m_model.GetWorldMatrix();
		D3DXVECTOR3 direction;
		direction.x = matrix.m[2][0];
		direction.y = matrix.m[2][1];
		direction.z = matrix.m[2][2];
		D3DXVec3Normalize(&direction, &direction);
		return direction;
	}
private:
	/*!
	*@brief	�L���[�̏��
	*/
	enum State {
		State_Search,	//�T��
		State_Find,		//����
		State_Miss,		//������
		State_Dead,		//���S
		State_Hit,		//�v���C���[�Ƀq�b�g
	};

	State				m_state = State_Search;				//���

	SkinModel			m_model;							//�X�L�����f��
	SkinModelData		m_modelData;						//�X�L�����f���f�[�^
	Light				m_light;							//���C�g
	D3DXVECTOR3			m_position;							//���W
	D3DXQUATERNION		m_rotation;							//��]
	D3DXVECTOR3			m_initPosition;						//�����ʒu
	D3DXQUATERNION		m_initRotation;						//������]
	float				m_moveLimitLine[4];					//�ړ����E���C��
	RigidBody			m_rigidBody;						//����
	D3DXVECTOR3			m_moveDir = { 0.0f,0.0f,0.0f };		//���������Ƃ��̈ړ�����
	const float			m_moveSpeed = 5.5f;					//�ړ����x
	bool				m_isDead = false;					//���S�t���O
	bool				m_isRespawn = false;				//���X�|�[���t���O
	float				m_timer = 0.0f;						//�^�C�}�[
	bool				m_hitPlayer = false;				//�v���C���[�ɓ��������t���O
	CParticleEmitter	m_particleEmitter;					//�p�[�e�B�N������
};