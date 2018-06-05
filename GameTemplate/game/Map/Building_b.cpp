#include "stdafx.h"
#include "Building_b.h"
#include "Scene/SceneManager.h"

Building_b::Building_b()
{
}

Building_b::~Building_b()
{
}

void Building_b::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation)
{
	m_modelData.LoadModelData("Assets/modelData/Building_b.x", NULL);
	m_model.Init(&m_modelData);
	//���C�g��������
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetAmbientLight(D3DXVECTOR4(0.6f, 0.6f, 0.6f, 1.0f));
	m_model.SetLight(&m_light);
	m_model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });

	m_position = position;
	m_rotation = rotation;

	//�Փ˔���̏�����
	//�X�L�����f�����烁�b�V���R���C�_�[���쐬����
	D3DXMATRIX* rootBoneMatrix = m_modelData.GetRootBoneWorldMatrix();
	m_meshCollider.CreateFromSkinModel(&m_model, rootBoneMatrix);

	//���̂���邽�߂̏���ݒ�
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider;		//���̂̃R���W������ݒ肷��
	rbInfo.mass = 0.0f;					//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	//���̂��쐬
	m_rigidBody.Create(rbInfo);

	//�쐬�������̂𕨗����[���h�ɒǉ�
	g_physicsWorld->AddRigidBody(&m_rigidBody);
}

void Building_b::Update()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		//���̂��폜
		g_physicsWorld->RemoveRigidBody(&m_rigidBody);
		return;
	}

	D3DXVECTOR3 toPlayerPos = player->GetPosition() - m_position;
	float length = D3DXVec3Length(&toPlayerPos);
	if (length <= 10.0f) {
		sceneManager->GetstageSelectScene()->SetBottonReneder(true, 1);
		if (pad->IsTrigger(pad->enButtonA)) {
			sceneManager->GetstageSelectScene()->SetChangeStage(true, 2);
		}
	}
	else {
		sceneManager->GetstageSelectScene()->SetBottonReneder(false, 1);
	}
}

void Building_b::Render()
{
	m_model.SetDrawShadowMap(false, true);
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}
