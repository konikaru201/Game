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

	void DepthStencilRender(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix);

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
		m_moveSpeed = moveSpeed;
		//m_characterController.SetMoveSpeed(moveSpeed);
	}

	//���܂ꂽ�t���O���擾
	bool GetIsStepOn()
	{
		return m_isStepOn;
	}

	bool GetIsOnMoveFloor()
	{
		return moveFloorHit;
	}

	bool GetIsOnMoveFloor2()
	{
		return moveFloor2Hit;
	}

	const D3DXVECTOR3& GetMoveFloorPosition()
	{
		return moveFloorPosition;
	}

	const D3DXVECTOR3& GetMoveFloor2Position()
	{
		return moveFloor2Position;
	}
private:
	SkinModel					m_model;							//�X�L�����f��
	SkinModelData				m_modelData;						//�X�L�����f���f�[�^
	Light						m_light;							//���C�g
	D3DXVECTOR3					m_position;							//���W
	D3DXQUATERNION				m_rotation;							//��]
	D3DXVECTOR3					m_scale;							//�g��
	D3DXVECTOR3					m_direction;						//����
	Animation					m_animation;						//�A�j���[�V����
	D3DXVECTOR3					m_moveSpeed = { 0.0f,0.0f,0.0f };	//�ړ����x
	CharacterController			m_characterController;				//�L�����N�^�[�R���g���[���[
	StoneMonsterStateMachine	m_stoneMonsterStateMachine;			//�X�e�[�g�}�V��

	D3DXMATRIX parentWorldMatrix;									//�e�̃��[���h�s��
	D3DXVECTOR3 childPosition = { 0.0f,0.0f,0.0f };					//�e�̃��[�J�����W����݂����W
	bool moveFloorHit = false;
	D3DXVECTOR3 moveFloorPosition = { 0.0f,0.0f,0.0f };

	D3DXMATRIX secondParentWorldMatrix;								//�e�̃��[���h�s��
	D3DXVECTOR3 secondChildPosition = { 0.0f,0.0f,0.0f };			//�e�̃��[�J�����W����݂��v���C���[�̍��W
	bool moveFloor2Hit = false;
	D3DXVECTOR3 moveFloor2Position = { 0.0f,0.0f,0.0f };

	float m_deadTimer = 0.0f;
	bool m_isStepOn = false;
	bool m_isHitPlaer = false;
};