#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"

class MapChip : public GameObject
{
public:
	//�R���X�g���N�^
	MapChip();

	//�f�X�g���N�^
	~MapChip();

	//������
	//modelName		���f���l�[��
	//position		���W
	//rotation		��]
	void Init(const char* modelName, D3DXVECTOR3 position, D3DXQUATERNION rotation);

	//�X�V
	void Update();

	//�`��
	void Render();
private:
	SkinModel model;				//�X�L�����f��
	SkinModelData modelData;		//�X�L�����f���f�[�^
	MeshCollider meshCollider;		//���b�V���R���C�_�[
	RigidBody rigidBody;			//����
	Light light;					//���C�g
};

