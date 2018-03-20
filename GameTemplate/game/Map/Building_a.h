#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"

class Building_a : public GameObject {
public:
	//�R���X�g���N�^
	Building_a();
	//�f�X�g���N�^
	~Building_a();

	//������
	//position		���W
	//rotation		��]
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation);

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
	D3DXVECTOR3 m_position;
	D3DXQUATERNION m_rotation;
};