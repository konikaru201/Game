#include "stdafx.h"
#include "Floor.h"
#include "Scene/SceneManager.h"

Floor::Floor()
{
}

Floor::~Floor()
{
}

void Floor::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	modelData.LoadModelData("Assets/modelData/MoveFloor_3.x", NULL);
	model.Init(&modelData);
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

	model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0 }, { 1.0f,1.0f,1.0f });

	position = pos;
	rotation = rot;

	BoxCollider* boxCollider = new BoxCollider;
	boxCollider->Create(D3DXVECTOR3(2.5f, 0.41f, 2.5f));

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
	trans.setOrigin(btVector3(position.x, position.y, position.z));

	//�쐬�������̂𕨗����[���h�ɒǉ�
	g_physicsWorld->AddRigidBody(&rigidBody);
}

void Floor::Update()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		//���̂��폜
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}

	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
}

void Floor::Render()
{
	model.SetDrawShadowMap(false, true);
	model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}
