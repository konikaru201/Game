#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

class Spring : public GameObject
{
public:
	//�R���X�g���N�^
	Spring();

	//�f�X�g���N�^
	~Spring();

	//������
	//pos	���W
	//rot	��]
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//�X�V
	void Update();

	//�`��
	void Render();

	//�v���C���[�Ƃ̓����蔻��
	void CollisionDetection();

	//�ړ����x���擾
	const D3DXVECTOR3& GetMoveSpeed()
	{
		return m_jumpSpeed;
	}

private:
	SkinModel m_model;									//�X�L�����f��
	SkinModelData m_modelData;							//�X�L�����f���f�[�^
	MeshCollider m_meshCollider;						//���b�V���R���C�_�[
	RigidBody m_rigidBody;								//����
	Light light;										//���C�g
	D3DXVECTOR3 m_position;								//���W
	D3DXQUATERNION m_rotation;							//��]
	D3DXVECTOR3 m_jumpSpeed = { 0.0f, 20.0f, 0.0f };	//�W�����v���x
};