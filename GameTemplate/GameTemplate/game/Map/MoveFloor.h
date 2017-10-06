#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"

class MoveFloor : public GameObject 
{
public:
	//�R���X�g���N�^
	MoveFloor();

	//�f�X�g���N�^
	~MoveFloor();

	//������
	//pos	���W
	//rot	��]
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//�X�V
	void Update();

	//�`��
	void Render();
	
	//�ړ�
	void Move();

	//�ړ����x���擾
	D3DXVECTOR3& GetMoveSpeed()
	{
		return moveSpeed;
	}

	//�ړ��t���O�̎擾
	bool GetMoveFlag()
	{
		return MoveFlag;
	}
private:
	SkinModel model;								//�X�L�����f��
	SkinModelData modelData;						//�X�L�����f���f�[�^
	MeshCollider meshCollider;						//���b�V���R���C�_�[
	RigidBody rigidBody;							//����

	D3DXVECTOR3 position;							//���W
	D3DXQUATERNION rotation;						//��]
	D3DXVECTOR3 moveSpeed = { 0.07f,0.0f,0.0f };	//�ړ����x
	float Timer = 0.0f;								//�^�C�}�[
	bool MoveFlag = false;							//�ړ��t���O
};