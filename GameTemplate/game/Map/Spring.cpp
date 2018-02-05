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
	m_modelData.LoadModelData("Assets/modelData/Spring.x", NULL);
	m_model.Init(&m_modelData);
	m_model.SetLight(&gameScene->GetLight());
	m_model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0 }, { 1.0f,1.0f,1.0f });

	m_position = pos;
	m_rotation = rot;

	//�Փ˔���̏�����
	//�X�L�����f�����烁�b�V���R���C�_�[���쐬����
	D3DXMATRIX* rootBoneMatrix = m_modelData.GetRootBoneWorldMatrix();
	m_meshCollider.CreateFromSkinModel(&m_model, rootBoneMatrix);

	//���̂���邽�߂̏���ݒ�
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider;		//���̂̃R���W������ݒ肷��
	rbInfo.mass = 0.0f;					//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	//���̂��쐬
	m_rigidBody.Create(rbInfo);

	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));

	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_JumpBlock);
	m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	m_rigidBody.GetBody()->setActivationState(DISABLE_DEACTIVATION);

	//�쐬�������̂𕨗����[���h�ɒǉ�
	g_physicsWorld->AddRigidBody(&m_rigidBody);
}

void Spring::Update()
{
	if (gameScene == nullptr || gameScene->GetChengeStage()) {
		SetisDead();
		//���̂��폜
		g_physicsWorld->RemoveRigidBody(&m_rigidBody);
		return;
	}

	//�v���C���[�Ƃ̓����蔻��
	CollisionDetection();

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f });
}

void Spring::Render()
{
	if (gameScene == nullptr) { return; }
	m_model.SetDrawShadowMap(false, true);
	m_model.Draw(&gameScene->GetGameCamera()->GetViewMatrix(), &gameScene->GetGameCamera()->GetViewProjectionMatrix());
}

void Spring::CollisionDetection()
{
	D3DXVECTOR3 toPlayerPos = g_player->GetPosition() - m_position;
	float length = D3DXVec3Length(&toPlayerPos);
	if (length <= 3.0f)
	{
		D3DXVECTOR3 toPlayerPosY = { 0.0f,toPlayerPos.y,0.0f };
		float lengthY = D3DXVec3Length(&toPlayerPosY);

		//Y�����ɓ�������
		if (toPlayerPosY.y >= 2.0f && lengthY <= 2.5f) {
			g_player->SetTreadOnSpring(true);
		}
	}
}
