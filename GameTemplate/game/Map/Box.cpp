#include "stdafx.h"
#include "Box.h"
#include "../Scene/GameScene.h"
#include "myEngine/Physics/CollisionAttr.h"

Box::Box()
{
}

Box::~Box()
{
}

void Box::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	modelData.LoadModelData("Assets/modelData/Box.x", NULL);
	model.Init(&modelData);
	model.SetLight(&gameScene->GetLight());
	model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0 }, { 1.0f,1.0f,1.0f });

	position = pos;
	rotation = rot;

	BoxCollider* boxCollider = new BoxCollider;
	boxCollider->Create(D3DXVECTOR3(2.5f, 2.5f, 2.5f));

	D3DXVECTOR3 rigidPos = position;
	rigidPos.y += 2.5f;

	//���̂̍쐬
	//���̂���邽�߂̏���ݒ�
	RigidBodyInfo rbInfo;
	rbInfo.collider = boxCollider;	//���̂̃R���W������ݒ肷��
	rbInfo.mass = 0.0f;				//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	//���̂��쐬
	rigidBody.Create(rbInfo);
	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	//���̂̈ʒu���X�V�B
	trans.setOrigin(btVector3(rigidPos.x, rigidPos.y, rigidPos.z));

	//rigidBody.GetBody()->setUserIndex(enCollisionAttr_Box);
	//rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	//rigidBody.GetBody()->setActivationState(DISABLE_DEACTIVATION);

	//�쐬�������̂𕨗����[���h�ɒǉ�
	g_physicsWorld->AddRigidBody(&rigidBody);
}

void Box::Update()
{
	if (gameScene == nullptr || gameScene->GetChengeStage()) {
		SetisDead();
		//���̂��폜
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}

	//if (g_player != nullptr) {
	//	if (g_player->GetIsOnBox() == true) {
	//		D3DXVECTOR3 playerPos = g_player->GetPosition();

	//		if (position.x - 2.5f < playerPos.x < position.x + 2.5f
	//			&& position.z + 2.5f < playerPos.z < position.z - 2.5f)
	//		{
	//			Hit = true;
	//		}
	//	}
	//}


	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
}

void Box::Render()
{
	if (gameScene == nullptr) { return; }
	model.SetDrawShadowMap(false, true);
	model.Draw(&gameScene->GetGameCamera()->GetViewMatrix(), &gameScene->GetGameCamera()->GetViewProjectionMatrix());
}
