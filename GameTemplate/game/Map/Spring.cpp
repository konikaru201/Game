#include "stdafx.h"
#include "Spring.h"
#include "Scene/GameScene.h"
#include "myEngine/Physics/CollisionAttr.h"

Spring::Spring()
{
}

Spring::~Spring()
{
}

void Spring::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	modelData.LoadModelData("Assets/modelData/Spring.x", NULL);
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

	rigidBody.GetBody()->setUserIndex(enCollisionAttr_JumpBlock);
	rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	rigidBody.GetBody()->setActivationState(DISABLE_DEACTIVATION);

	//�쐬�������̂𕨗����[���h�ɒǉ�
	g_physicsWorld->AddRigidBody(&rigidBody);
}

void Spring::Update()
{
	if (gameScene == nullptr || gameScene->GetChengeStage()) {
		SetisDead();
		//���̂��폜
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}

	//D3DXVECTOR3 playerPos = g_player->GetPosition();
	//D3DXVECTOR3 toPlayerPos = playerPos - position;
	//float length = D3DXVec3Length(&toPlayerPos);
	//if (length < 1.0f) {
	//	MoveFlg = true;
	//}

	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });

}

void Spring::Render()
{
	if (gameScene == nullptr) { return; }
	model.SetDrawShadowMap(false, true);
	model.Draw(&gameScene->GetGameCamera()->GetViewMatrix(), &gameScene->GetGameCamera()->GetViewProjectionMatrix());
}

void Spring::Move()
{
}
