#pragma once

#include "myEngine/Physics/BoxCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

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

	void PostRender();
private:
	enum State {
		Entity,		//����
		Clear		//����
	};
	State m_state = Entity;

	SkinModel model;								//�X�L�����f��
	SkinModelData modelData;						//�X�L�����f���f�[�^
	RigidBody rigidBody;							//����
	Light light;									//���C�g
	D3DXVECTOR3 position;							//���W
	D3DXQUATERNION rotation;						//��]
	float m_timer = 0.0f;			//�^�C�}�[
	float m_alpha = 1.0f;			//�s�����x�B0.0�œ���
	const float ALPHA_TIME = 0.5f;
	float m_alphaTimer = 0.0f;
};