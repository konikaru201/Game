#include "stdafx.h"
#include "MapChip.h"
#include "Scene/GameScene.h"
#include "myEngine/GameObject/GameObjectManager.h"

MapChip::MapChip()
{
}

MapChip::~MapChip()
{
	//���̂��폜
	g_physicsWorld->RemoveRigidBody(&rigidBody);
	//rigidBody.Release();
}

void MapChip::Init(const char* modelName, D3DXVECTOR3 position, D3DXQUATERNION rotation)
{
	//�ǂݍ��ރ��f���̃t�@�C���p�X���쐬
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//���f�������[�h
	modelData.LoadModelData(filePath, NULL);
	//���[�h�������f���f�[�^���g����SkinModel��������
	model.Init(&modelData);

	model.SetLight(&gameScene->GetLight());

	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
	//�Փ˔���̏�����
	//�X�L�����f�����烁�b�V���R���C�_�[���쐬����
	D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);
	//���̂̍쐬
	//���̂���邽�߂̏���ݒ�
	RigidBodyInfo rbInfo;
	rbInfo.collider = &meshCollider;	//���̂̃R���W������ݒ肷��
	rbInfo.mass = 0.0f;					//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	//���̂��쐬
	rigidBody.Create(rbInfo);
	//�쐬�������̂𕨗����[���h�ɒǉ�
	g_physicsWorld->AddRigidBody(&rigidBody);
}

void MapChip::Update()
{
	if (gameScene == nullptr || gameScene->GetChengeStage()) {
		SetisDead();
		//���̂��폜
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}
}

void MapChip::Render()
{
	if (gameScene == nullptr) { return; }
	model.Draw(&gameScene->GetGameCamera()->GetViewMatrix(), &gameScene->GetGameCamera()->GetViewProjectionMatrix());
}