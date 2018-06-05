/*!
*@brief	���b�h�h���S���N���X
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Graphics/ParticleEmitter.h"
#include "myEngine/Graphics/Light.h"

class Red_Dragon : public GameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	Red_Dragon();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~Red_Dragon();
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
	* @param[in]	length		����
	* @param[in]	toPlayer	�v���C���[�ւ̃x�N�g��
	*/
	void CollisionDetection(float length, const D3DXVECTOR3& toPlayer);
	/*!
	* @brief	�e��`��
	* @param[in]	viewMatrix		�r���[�s��
	* @param[in]	projMatrix		�v���W�F�N�V�����s��
	* @param[in]	isDrawShadowMap	�V���h�E�}�b�v��`���t���O
	* @param[in]	isRecieveShadow	�V���h�E���V�[�o�[���ǂ���
	*/
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);
	/*!
	* @brief	���b�h�h���S���̌������擾
	*@return	���b�h�h���S���̌���
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
	*@brief	�A�j���[�V�����̏��
	*/
	enum AnimationNo {
		AnimationWait,		//�ҋ@
		AnimationRun,		//����ړ�
		AnimationAttack,	//�U��
		AnimationDead,		//���S
	};
	/*!
	*@brief	���b�h�h���S���̏��
	*/
	enum State {
		State_Wait,		//�ҋ@
		State_Move,		//�ړ�
		State_Find,		//����
		State_Miss,		//������
		State_Attack,	//�U��
		State_Dead,		//���S
		State_Hit,		//�v���C���[�Ƀq�b�g
	};

	State				m_state = State_Wait;
	AnimationNo			m_currentAnim;
	AnimationNo			m_prevAnim;

	SkinModel			m_model;						//�X�L�����f��
	SkinModelData		m_modelData;					//�X�L�����f���f�[�^
	Light				m_light;						//���C�g
	D3DXVECTOR3			m_position;						//���W
	D3DXVECTOR3			m_initPosition;					//�������W
	D3DXQUATERNION		m_rotation;						//��]
	RigidBody			m_rigidBody;					//����
	Animation			m_animation;					//�A�j���[�V����
	D3DXVECTOR3			m_moveDir = { 0.0f,0.0f,0.0f };	//�ړ�����
	D3DXVECTOR3			m_up = { 0.0f,1.0f,0.0f };		//�����
	float				m_moveSpeed = 2.0f;				//�ړ����x
	D3DXMATRIX*			m_matrix;						//�{�[���̃��[���h�s��
	float				m_timer = 0.0f;					//�^�C�}�[
	float				m_soundTimer = 0.0f;			//���̃^�C�}�[
	float				m_attackTimer = 0.0f;			//�v���C���[���U���ɓ������Ă��鎞��
	D3DXVECTOR3			m_XDir = { 1.0f,0.0f,0.0f };	//X����
	bool				m_findAgainFlag = false;		//�U����Ɏ��E���Ƀv���C���[�����邩
	bool				m_changeDir = true;				//�����]���̃t���O
	CParticleEmitter	m_particleEmitter;				//�p�[�e�B�N������
	bool				m_hitPlayer = false;			//�v���C���[�ɓ��������t���O
	bool				m_isDead = false;				//���S�t���O
};