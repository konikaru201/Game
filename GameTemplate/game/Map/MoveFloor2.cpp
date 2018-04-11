#include "stdafx.h"
#include "MoveFloor2.h"
#include "Scene/SceneManager.h"
#include "myEngine/Physics/CollisionAttr.h"
#include "myEngine/Timer/Timer.h"
#include "Player/Player.h"

MoveFloor2::MoveFloor2()
{
}

MoveFloor2::~MoveFloor2()
{
}

void MoveFloor2::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	modelData.LoadModelData("Assets/modelData/MoveFloor_2.x", NULL);
	model.Init(&modelData);
	//���C�g�̐ݒ�
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.6f, 0.6f, 0.6f, 1.0f));
	model.SetLight(&light);

	model.UpdateWorldMatrix(pos, rot, { 1.0f,1.0f,1.0f });

	position = pos;
	rotation = rot;
	moveSpeed = { -0.05f,0.0f,0.0f };

	//�Փ˔���̏�����
	//�X�L�����f������{�b�N�X�R���C�_�[���쐬����
	BoxCollider* boxCollider = new BoxCollider;
	boxCollider->Create(D3DXVECTOR3(2.5f, 0.41f, 2.5f));

	//���̂���邽�߂̏���ݒ�
	RigidBodyInfo rbInfo;
	rbInfo.collider = boxCollider;		//���̂̃R���W������ݒ肷��
	rbInfo.mass = 0.0f;					//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	//���̂��쐬
	rigidBody.Create(rbInfo);

	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(position.x, position.y, position.z));

	rigidBody.GetBody()->setUserIndex(enCollisionAttr_MoveFloor2);
	rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	rigidBody.GetBody()->setActivationState(DISABLE_DEACTIVATION);

	//�쐬�������̂𕨗����[���h�ɒǉ�
	g_physicsWorld->AddRigidBody(&rigidBody);
}

bool MoveFloor2::Start()
{
	
	return true;
}

void MoveFloor2::Update()
{
	
}
void MoveFloor2::PreUpdate()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		//���̂��폜
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}

	Move();

	if (moveFlg) {
		player->SetMoveFloor2Speed(moveSpeed);
	}
	else {
		player->SetMoveFloor2Speed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(position.x, position.y, position.z));

	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
}

void MoveFloor2::Move()
{
	Timer += Timer::GetFrameDeltaTime();
	moveFlg = true;
	if (Timer >= 10.0f) {
		moveSpeed *= -1.0f;
		Timer = 0.0f;
	}
	if (Timer >= 2.0f)
	{
		position += moveSpeed;
	}
	else
	{
		moveFlg = false;
	}
}

void MoveFloor2::Render()
{
	model.SetDrawShadowMap(false, true);
	model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}