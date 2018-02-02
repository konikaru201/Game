#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Graphics/ParticleEmitter.h"

class Red_Dragon : public GameObject
{
public:
	//�R���X�g���N�^
	Red_Dragon();

	//�f�X�g���N�^
	~Red_Dragon();

	//������
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//�X�V
	void Update();

	//�`��
	void Render();

	//�ړ�
	D3DXVECTOR3 Move();

	//�v���C���[�Ƃ̓����蔻��
	void CollisionDetection(float Length, const D3DXVECTOR3& ToPlayer);

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
	enum AnimationNo {
		AnimationWait,		//�ҋ@
		AnimationRun,		//����ړ�
		AnimationAttack,	//�U��
	};

	enum State {
		State_Wait,		//�ҋ@
		State_Move,		//�ړ�
		State_Find,		//����
		State_Miss,		//������
		State_Attack,	//�U��
		State_Dead,		//���S
		State_Hit,		//�v���C���[�Ƀq�b�g
	};

	State state = State_Wait;
	AnimationNo currentAnim;
	AnimationNo prevAnim;

	SkinModel			model;							//�X�L�����f��
	SkinModelData		modelData;						//�X�L�����f���f�[�^
	D3DXVECTOR3			position;						//���W
	D3DXVECTOR3			initPosition;					//�������W
	D3DXQUATERNION		rotation;						//��]
	RigidBody			rigidBody;						//����
	Animation			animation;						//�A�j���[�V����
	D3DXVECTOR3			moveDir = { 0.0f,0.0f,0.0f };	//�ړ�����
	D3DXVECTOR3			up = { 0.0f,1.0f,0.0f };		//�����
	float				moveSpeed = 2.0f;				//�ړ����x
	D3DXMATRIX*			matrix;							//�{�[���̃��[���h�s��
	float				timer = 0.0f;					//�^�C�}�[
	float				soundTimer = 0.0f;				//���̃^�C�}�[
	D3DXVECTOR3			XDir = { 1.0f,0.0f,0.0f };		//X����
	bool				findAgainFlag = false;			//�U����Ɏ��E���Ƀv���C���[�����邩
	bool				changeDir = true;				//�����]���̃t���O
	CParticleEmitter	particleEmitter;				//�p�[�e�B�N������
	bool				m_hitPlayer = false;			//�v���C���[�ɓ��������t���O
	bool				isDead = false;					//���S�t���O
};