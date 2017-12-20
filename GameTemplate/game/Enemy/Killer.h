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
private:
	enum State {
		State_Search,	//�T��
		State_Find,		//����
		State_Miss,		//������
	};

	State				state = State_Search;			//���

	SkinModel			model;							//�X�L�����f��
	SkinModelData		modelData;						//�X�L�����f���f�[�^
	CharacterController characterController;			//�L�����N�^�[�R���g���[���[

	D3DXVECTOR3			position;						//���W
	D3DXQUATERNION		rotation;						//��]
	D3DXVECTOR3			InitPosition;					//�����ʒu
	RigidBody			rigidBody;						//����
	D3DXVECTOR3			up = { 0.0f,1.0f,0.0f };
	D3DXVECTOR3			moveDir = { 0.0f,0.0f,0.0f };
	const float			moveSpeed = 4.0f;				//�ړ����x
};