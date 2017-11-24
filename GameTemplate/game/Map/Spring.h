#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"

class Spring : public GameObject
{
public:
	Spring();
	~Spring();
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

	////�ړ��t���O���擾
	//bool GetMoveFlg()
	//{
	//	return MoveFlg;
	//}
private:
	SkinModel model;								//�X�L�����f��
	SkinModelData modelData;						//�X�L�����f���f�[�^
	MeshCollider meshCollider;						//���b�V���R���C�_�[
	RigidBody rigidBody;							//����

	D3DXVECTOR3 position;							//���W
	D3DXQUATERNION rotation;						//��]
	D3DXVECTOR3 moveSpeed = { 0.0f, 20.0f, 0.0f };	//�ړ����x
	bool MoveFlg = false;

};