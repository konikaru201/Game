#include "stdafx.h"
#include "MoveFloor2.h"
#include "Scene/GameScene.h"
#include "myEngine/Physics/CollisionAttr.h"
#include "myEngine/Timer/Timer.h"

MoveFloor2* g_moveFloor2;

MoveFloor2::MoveFloor2()
{
}

MoveFloor2::~MoveFloor2()
{
	//g_physicsWorld->RemoveRigidBody(&rigidBody);
	//rigidBody.Release();
}

void MoveFloor2::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	modelData.LoadModelData("Assets/modelData/MoveFloor_2.x", NULL);
	model.Init(&modelData);
	model.SetLight(&gameScene->GetLight());
	model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0 }, { 1.0f,1.0f,1.0f });

	position = pos;
	rotation = rot;

	//�Փ˔���̏�����
	//�X�L�����f�����烁�b�V���R���C�_�[���쐬����
	D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);

	//���̂���邽�߂̏���ݒ�
	RigidBodyInfo rbInfo;
	rbInfo.collider = &meshCollider;		//���̂̃R���W������ݒ肷��
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

void MoveFloor2::Update()
{
	
}
void MoveFloor2::PreUpdate()
{
	if (gameScene == nullptr) {
		SetisDead();
		g_moveFloor2 = nullptr;
		//���̂��폜
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}

	Move();

	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(position.x, position.y, position.z));

	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
}
void MoveFloor2::Move()
{
	Timer += Timer::GetFrameDeltaTime();
	moveFlg = true;
	if (Timer >= 7.0f) {
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
	if (gameScene == nullptr) { return; }
	model.SetDrawShadowMap(false, true);
	model.Draw(&gameScene->GetGameCamera()->GetViewMatrix(), &gameScene->GetGameCamera()->GetViewProjectionMatrix());
}