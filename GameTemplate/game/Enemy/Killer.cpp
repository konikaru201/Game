#include "stdafx.h"
#include "Killer.h"
#include "Scene/GameScene.h"
#include "myEngine/Physics/CollisionAttr.h"

Killer::Killer()
{
}

Killer::~Killer()
{
	//characterController.RemoveRigidBoby();
	//characterController.~CharacterController();
}

void Killer::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	//���f���̏�����
	modelData.LoadModelData("Assets/modelData/Killer.x", NULL);
	model.Init(&modelData);
	model.SetLight(&gameScene->GetLight());
	model.UpdateWorldMatrix( pos, rot, { 1.0f,1.0f,1.0f });

	position = pos;
	rotation = rot;
	InitPosition = pos;

	state = State_Search;

	//���̂̍쐬
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(1.0f, 1.0f);
	characterController.Init(coll, position);

	characterController.GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Killer);
}

void Killer::Update()
{
	if (gameScene == nullptr || gameScene->GetChengeStage()) {
		SetisDead();
		//���̂��폜
		characterController.RemoveRigidBoby();
		return;
	}

	//�ړ����x��ݒ�
	characterController.SetMoveSpeed(Move());
	//�L�����N�^�[�R���g���[���[�����s
	characterController.Execute();
	//���W��ݒ�
	position = characterController.GetPosition();

	//�����ʒu�ɖ߂�
	if (position.z >= -40.0f)
	{
		position = InitPosition;
		characterController.SetPosition(position);
	}

	model.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Killer::Render()
{
	if (gameScene == nullptr) { return; }
	model.Draw(&gameScene->GetGameCamera()->GetViewMatrix(), &gameScene->GetGameCamera()->GetViewProjectionMatrix());
}

D3DXVECTOR3 Killer::Move()
{
	//�ړ����x���擾
	D3DXVECTOR3 move = characterController.GetMoveSpeed();

	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 toPlayer = gameScene->GetPlayer()->GetPosition() - position;
	//���f����Z�������擾
	D3DXVECTOR3 direction;
	D3DXMATRIX mWorld = model.GetWorldMatrix();
	direction.x = mWorld.m[2][0];
	direction.y = mWorld.m[2][1];
	direction.z = mWorld.m[2][2];

	float length = 0.0f;
	float angle = 0.0f;
	D3DXVECTOR3 AxisZ = { 0.0f,0.0f,1.0f };
	D3DXVECTOR3 up = { 0.0f,1.0f,0.0f };
	switch (state)
	{
	//�T�����
	case State_Search:
		length = D3DXVec3Length(&toPlayer);
		D3DXVec3Normalize(&toPlayer, &toPlayer);
		angle = D3DXVec3Dot(&toPlayer, &direction);
		angle = acos(angle);

		//�������ꂽ
		if (fabsf(angle) < D3DXToRadian(45.0f) && length < 5.0f) {
			state = State_Find;
		}

		move.z = 2.0f;

		break;
	//�������
	case State_Find:
		length = D3DXVec3Length(&toPlayer);
		D3DXVec3Normalize(&toPlayer, &toPlayer);
		angle = D3DXVec3Dot(&toPlayer, &AxisZ);
		angle = acos(angle);
		if (toPlayer.x <= 0.0f) {
			angle *= -1.0f;
		}
		D3DXVec3Scale(&toPlayer, &toPlayer, MoveSpeed);
		move = toPlayer;
		
		D3DXQuaternionRotationAxis(&rotation, &up, angle);
		break;
	default:
		break;
	}

	return move;
}