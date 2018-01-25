#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"

class SkyBox : public GameObject
{
public:
	//�R���X�g���N�^
	SkyBox();

	//�f�X�g���N�^
	~SkyBox();

	//������
	//pos	���W
	//rot	��]
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//�A�b�v�f�[�g���Ă΂��O�ɌĂ΂��֐�
	bool Start();

	//�X�V
	void Update();

	//�`��
	void Render();
private:
	SkinModel model;								//�X�L�����f��
	SkinModelData modelData;						//�X�L�����f���f�[�^
	MeshCollider meshCollider;						//���b�V���R���C�_�[
	RigidBody rigidBody;							//����
	D3DXVECTOR3 rotationAxis;
	D3DXVECTOR3 position;							//���W
	D3DXQUATERNION rotation;						//��]
	Light light;									//���C�g
	
	LPDIRECT3DCUBETEXTURE9	m_cubeMapTexture = nullptr;
};