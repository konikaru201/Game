#pragma once

#include "myEngine/Physics/CharacterController.h"
#include "myEngine/GameObject/GameObject.h"

class Killer : public GameObject {
public:
	//�R���X�g���N�^
	Killer();

	//�f�X�g���N�^
	~Killer();

	//������
	//pos	���W
	//rot	��]
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//�X�V
	void Update();

	//�`��
	void Render();

	//�ړ�
	D3DXVECTOR3 Move();

	//�v���C���[�Ƃ̓����蔻��
	void CollisionDetection(float Length , const D3DXVECTOR3& ToPlayer);
private:
	enum State {
		State_Search,	//�T��
		State_Find,		//����
		State_Miss,		//������
		State_Dead,		//���S
	};

	State				state = State_Search;				//���

	SkinModel			model;								//�X�L�����f��
	SkinModelData		modelData;							//�X�L�����f���f�[�^
	CharacterController characterController;				//�L�����N�^�[�R���g���[���[

	D3DXVECTOR3			position;							//���W
	D3DXQUATERNION		rotation;							//��]
	D3DXVECTOR3			InitPosition;						//�����ʒu
	float				moveLimitLine[4];					//�ړ����E���C��
	RigidBody			rigidBody;							//����
	D3DXVECTOR3			moveDir = { 0.0f,0.0f,0.0f };		//���������Ƃ��̈ړ�����
	const float			moveSpeed = 4.0f;					//�ړ����x
	bool				isDead = false;						//���S�t���O
	float				timer = 0.0f;						//�^�C�}�[
	bool				m_hitPlayer = false;				//�v���C���[�ɓ��������t���O
	D3DXVECTOR3			m_toPlayer = { 0.0f,0.0f,0.0f };	//���������Ƃ��Ƀv���C���[�ւ̃x�N�g����ێ�
};