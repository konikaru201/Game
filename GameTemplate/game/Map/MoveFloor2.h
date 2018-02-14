#pragma once

#include "myEngine/Physics/MeshCollider.h"
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

	//Update�֐����O�ɌĂ΂��X�V�֐�
	void PreUpdate();

	//�X�V
	void Update();
	
	//�`��
	void Render();

	//�ړ�
	void Move();

	//�ړ����x���擾
	const D3DXVECTOR3& GetMoveSpeed()
	{
		return moveSpeed;
	}

	//�ړ��t���O�̎擾
	bool GetmoveFlg()
	{
		return moveFlg;
	}
private:
	SkinModel model;								//�X�L�����f��
	SkinModelData modelData;						//�X�L�����f���f�[�^
	MeshCollider meshCollider;						//���b�V���R���C�_�[
	RigidBody rigidBody;							//����
	Light light;									//���C�g
	D3DXVECTOR3 position;							//���W
	D3DXQUATERNION rotation;						//��]
	D3DXVECTOR3 moveSpeed = { 0.0f,0.05f,0.0f };	//�ړ����x
	float Timer = 0.0f;								//�^�C�}�[
	bool moveFlg = false;							//�ړ��t���O
};

extern MoveFloor2* g_moveFloor2;