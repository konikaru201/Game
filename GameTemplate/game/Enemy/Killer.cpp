#include "stdafx.h"
#include "Killer.h"
#include "Scene/GameScene.h"
#include "myEngine/Physics/CollisionAttr.h"

Killer::Killer()
{
}

Killer::~Killer()
{
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

	////���̂̍쐬
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(1.0f, 1.0f);
	characterController.Init(coll, position);
	characterController.SetGravity(0.0f);

	//���̂���邽�߂̏���ݒ�
	RigidBodyInfo rbInfo;
	rbInfo.collider = coll;		//���̂̃R���W������ݒ肷��
	rbInfo.mass = 0.0f;			//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	//���̂��쐬
	rigidBody.Create(rbInfo);

	//�쐬�������̂𕨗����[���h�ɒǉ�
	g_physicsWorld->AddRigidBody(&rigidBody);

}

void Killer::Update()
{
	if (gameScene == nullptr || gameScene->GetChengeStage()) {
		SetisDead();
		//���̂��폜
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}

	//�����ʒu�ɖ߂�
	if (position.x < 55.0f || position.x > 130.0f
		|| position.z < -120.0f || position.z > -70.0f)
	{
		characterController.SetPosition(InitPosition);
		D3DXQuaternionRotationAxis(&rotation, &up, D3DXToRadian(-90.0f));
		state = State_Search;
	}

	D3DXVECTOR3 moveSpeed = Move();

	characterController.SetMoveSpeed(moveSpeed);
	characterController.Execute();
	position = characterController.GetPosition();

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
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };

	//�v���C���[�̈ʒu���擾
	D3DXVECTOR3 playerPos = g_player->GetPosition();
	D3DXVECTOR3 toPlayer = playerPos - position;
	//���f����Z�������擾
	D3DXVECTOR3 direction;
	D3DXMATRIX mWorld = model.GetWorldMatrix();
	direction.x = mWorld.m[2][0];
	direction.y = mWorld.m[2][1];
	direction.z = mWorld.m[2][2];

	float length = 0.0f;
	float angle = 0.0f;
	D3DXVECTOR3 AxisZ = { 0.0f,0.0f,1.0f };

	switch (state)
	{
	//�T�����
	case State_Search:
		length = D3DXVec3Length(&toPlayer);
		D3DXVec3Normalize(&toPlayer, &toPlayer);
		angle = D3DXVec3Dot(&toPlayer, &direction);
		angle = acos(angle);

		//�������ꂽ
		if (fabsf(angle) < D3DXToRadian(30.0f) && length < 12.0f) {
			state = State_Find;
		}

		move.x = -4.0f;

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
		move.y = 0.0f;

		//�v���C���[�Ƃ̋����������
		//���̓v���C���[�ɃW�����v�Ŕ�������ƌ�����
		if (length > 30.0f || (position.y + 1.0f < playerPos.y && position.x < playerPos.x)) {
			state = State_Miss;
			break;
		}

		D3DXQuaternionRotationAxis(&rotation, &up, angle);
		break;
	//�����������
	case State_Miss:
		moveDir = direction * MoveSpeed;
		move = moveDir;
		break;
	default:
		break;
	}

	return move;
}