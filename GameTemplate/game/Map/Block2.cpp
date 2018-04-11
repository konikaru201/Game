#include "stdafx.h"
#include "Block2.h"
#include "Scene/SceneManager.h"
#include "myEngine/Physics/CollisionAttr.h"
#include "../Player/Player.h"

Block2::Block2()
{
}

Block2::~Block2()
{
}

void Block2::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	modelData.LoadModelData("Assets/modelData/Block_2.x", NULL);
	model.Init(&modelData);
	//���C�g��ݒ�
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

	D3DXMATRIX matrix;
	D3DXMatrixRotationQuaternion(&matrix, &rotation);
	rotationAxis.x = matrix.m[0][0];
	rotationAxis.y = matrix.m[0][1];
	rotationAxis.z = matrix.m[0][2];
	D3DXVec3Normalize(&rotationAxis, &rotationAxis);

	//�Փ˔���̏�����
	//�X�L�����f�����烁�b�V���R���C�_�[���쐬����
	D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);

	//���̂���邽�߂̏���ݒ�
	RigidBodyInfo rbInfo;
	rbInfo.collider = &meshCollider;		//���̂̃R���W������ݒ肷��
	rbInfo.mass = 0.0f;						//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	//���̂��쐬
	rigidBody.Create(rbInfo);

	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(position.x, position.y, position.z));
	trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));

	rigidBody.GetBody()->setUserIndex(enCollisionAttr_Block2);
	rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	rigidBody.GetBody()->setActivationState(DISABLE_DEACTIVATION);

	//�쐬�������̂𕨗����[���h�ɒǉ�
	g_physicsWorld->AddRigidBody(&rigidBody);
}

bool Block2::Start()
{
	player->SetSecondParentWorldMatrix(GetWorldMatrix());
	return true;
}

void Block2::Update()
{
	if (sceneManager->GetChangeSceneFlag()) {
		SetisDead();
		//���̂��폜
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}

	float angle = 0.2f * cPI / 180.0f;
	D3DXQUATERNION rot = { 0.0f,1.0f,0.0f,1.0f };
	D3DXQuaternionRotationAxis(&rot, &rotationAxis, angle);
	D3DXQuaternionMultiply(&rotation, &rotation, &rot);

	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));

	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });

	player->SetSecondParentWorldMatrix(GetWorldMatrix());
}

void Block2::Render()
{
	model.SetDrawShadowMap(false, true);
	model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}
