#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Physics/CharacterController.h"
#include "StoneMonsterStateMachine.h"

class StoneMonster : public GameObject
{
public:
	StoneMonster();
	~StoneMonster();

	//������
	//pos	���W
	//rot	��]
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	bool Start();

	//�X�V
	void Update();

	//�`��
	void Render();

	//�e�̕`��
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);

	//���W���擾
	const D3DXVECTOR3& GetPosition()
	{
		return m_position;
	}

	//���W��ݒ�
	void SetPosition(const D3DXVECTOR3& position)
	{
		m_position = position;
	}

	//��]���擾
	const D3DXQUATERNION& GetRotation()
	{
		return m_rotation;
	}

	//��]��ݒ�
	void SetRotation(const D3DXQUATERNION& rotation)
	{
		m_rotation = rotation;
	}

	//���f���̌������擾
	const D3DXVECTOR3& GetDirection()
	{
		D3DXMATRIX matrix = m_model.GetWorldMatrix();
		m_direction.x = matrix.m[2][0];
		m_direction.y = matrix.m[2][1];
		m_direction.z = matrix.m[2][2];
		D3DXVec3Normalize(&m_direction, &m_direction);
		return m_direction;
	}

	//�ړ����x���擾
	const D3DXVECTOR3& GetMoveSpeed()
	{
		return m_characterController.GetMoveSpeed();
	}

	//�ړ����x��ݒ�
	void SetMoveSpeed(const D3DXVECTOR3& moveSpeed)
	{
		m_characterController.SetMoveSpeed(moveSpeed);
	}

private:
	SkinModel					m_model;							//�X�L�����f��
	SkinModelData				m_modelData;						//�X�L�����f���f�[�^
	Light						m_light;							//���C�g
	D3DXVECTOR3					m_position;							//���W
	D3DXQUATERNION				m_rotation;							//��]
	D3DXVECTOR3					m_direction;						//����
	Animation					m_animation;						//�A�j���[�V����
	D3DXVECTOR3					m_moveSpeed = { 0.0f,0.0f,0.0f };	//�ړ����x
	CharacterController			m_characterController;				//�L�����N�^�[�R���g���[���[
	StoneMonsterStateMachine	m_stoneMonsterStateMachine;			//�X�e�[�g�}�V��
};