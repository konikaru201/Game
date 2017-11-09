#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"

class Block : public GameObject
{
public:
	//�R���X�g���N�^
	Block();

	//�f�X�g���N�^
	~Block();

	//������
	//pos	���W
	//rot	��]
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	bool Start();

	//�X�V
	void Update();

	//�`��
	void Render();

	D3DXMATRIX GetWorldMatrix()
	{
		return model.GetWorldMatrix();
	}

	D3DXMATRIX GetRotationMatrix()
	{
		return model.GetRotationMatrix();
	}
private:
	SkinModel model;								//�X�L�����f��
	SkinModelData modelData;						//�X�L�����f���f�[�^
	MeshCollider meshCollider;						//���b�V���R���C�_�[
	RigidBody rigidBody;							//����
	D3DXVECTOR3 rotationAxis;
	D3DXVECTOR3 position;							//���W
	D3DXQUATERNION rotation;						//��]
};