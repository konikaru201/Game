#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"
#include "myEngine/Graphics/ParticleEmitter.h"
#include "myEngine/Physics/RigidBody.h"

class Killer : public GameObject {
public:
	//�R���X�g���N�^
	Killer();

	//�f�X�g���N�^
	~Killer();

	//������
	//pos	���W
	//rot	��]
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//�X�V
	void Update();

	//�`��
	void Render();

	//�ړ�
	D3DXVECTOR3 Move();

	//�v���C���[�Ƃ̓����蔻��
	void CollisionDetection(float Length , const D3DXVECTOR3& ToPlayer);

	//�e�̕`��
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);

	//���f���̌������擾
	D3DXVECTOR3 GetDirection()
	{
		D3DXMATRIX matrix = model.GetWorldMatrix();
		D3DXVECTOR3 direction;
		direction.x = matrix.m[2][0];
		direction.y = matrix.m[2][1];
		direction.z = matrix.m[2][2];
		D3DXVec3Normalize(&direction, &direction);
		return direction;
	}
private:
	enum State {
		State_Search,	//�T��
		State_Find,		//����
		State_Miss,		//������
		State_Dead,		//���S
		State_Hit,		//�v���C���[�Ƀq�b�g
	};

	State				state = State_Search;				//���

	SkinModel			model;								//�X�L�����f��
	SkinModelData		modelData;							//�X�L�����f���f�[�^
	Light				light;								//���C�g
	D3DXVECTOR3			position;							//���W
	D3DXQUATERNION		rotation;							//��]
	D3DXVECTOR3			initPosition;						//�����ʒu
	D3DXQUATERNION		initRotation;						//������]
	float				moveLimitLine[4];					//�ړ����E���C��
	RigidBody			rigidBody;							//����
	D3DXVECTOR3			moveDir = { 0.0f,0.0f,0.0f };		//���������Ƃ��̈ړ�����
	const float			moveSpeed = 5.5f;					//�ړ����x
	bool				isDead = false;						//���S�t���O
	bool				isRespawn = false;					//���X�|�[���t���O
	float				timer = 0.0f;						//�^�C�}�[
	bool				m_hitPlayer = false;				//�v���C���[�ɓ��������t���O
	CParticleEmitter	particleEmitter;					//�p�[�e�B�N������
};