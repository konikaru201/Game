#pragma once

#include "myEngine/Physics/BoxCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

class MoveFloor2 : public GameObject
{
public:
	//�R���X�g���N�^
	MoveFloor2();

	//�f�X�g���N�^
	~MoveFloor2();

	//������
	//pos	���W
	//rot	��]
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//�X�V����O�Ɉ�x�����Ă΂��֐�
	bool Start();

	//Update�֐����O�ɌĂ΂��X�V�֐�
	void PreUpdate();

	//�X�V
	void Update();
	
	//�`��
	void Render();

	//�ړ�
	void Move();

	const D3DXVECTOR3& GetPosition()
	{
		return position;
	}

	const D3DXMATRIX& GetWorldMatrix()
	{
		return model.GetWorldMatrix();
	}

private:
	SkinModel model;								//�X�L�����f��
	SkinModelData modelData;						//�X�L�����f���f�[�^
	RigidBody rigidBody;							//����
	Light light;									//���C�g
	D3DXVECTOR3 position;							//���W
	D3DXQUATERNION rotation;						//��]
	D3DXVECTOR3 moveSpeed /*= { -0.07f,0.0f,0.0f }*/;	//�ړ����x
	float Timer = 0.0f;								//�^�C�}�[
	bool moveFlg = false;							//�ړ��t���O
};