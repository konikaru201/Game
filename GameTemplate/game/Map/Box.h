#pragma once

#include "myEngine/Physics/BoxCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"

class Box : public GameObject
{
public:
	//�R���X�g���N�^
	Box();

	//�f�X�g���N�^
	~Box();

	//������
	//pos	���W
	//rot	��]
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//�X�V
	void Update();

	//�`��
	void Render();

private:
	SkinModel model;								//�X�L�����f��
	SkinModelData modelData;						//�X�L�����f���f�[�^
	RigidBody rigidBody;							//����
	D3DXVECTOR3 position;							//���W
	D3DXQUATERNION rotation;						//��]
};