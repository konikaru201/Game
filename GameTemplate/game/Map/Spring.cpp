#include "stdafx.h"
#include "Spring.h"
#include "Scene/SceneManager.h"
#include "myEngine/Physics/CollisionAttr.h"
#include "myEngine/sound/SoundSource.h"

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
	m_model.SetLight(&light);

	m_model.UpdateWorldMatrix({ 0.0f,0.0f,0.0f }, {0.0f,0.0f,0.0f,1.0f}, { 1.0f,1.0f,1.0f });

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

bool Spring::Start()
{
	D3DXMatrixIdentity(&parentWorldMatrix);
	//��ԋ߂��ړ����̃��[���h�s����擾
	if (!map->GetMoveFloor2List().empty()) {
		parentWorldMatrix = map->MoveFloor2WorldMatrix(m_position);
		moveFloor2Position = map->GetMoveFloor2Position(m_position);
		moveFloor2Find = true;
	}

	//�e�̃��[���h�s�񂩂�t�s��𐶐�
	D3DXMATRIX parentWorldMatrixInv;
	D3DXMatrixInverse(&parentWorldMatrixInv, NULL, &parentWorldMatrix);
	D3DXVec3TransformCoord(&childPosition, &m_position, &parentWorldMatrixInv);

	return true;
}

void Spring::Update()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		//���̂��폜
		g_physicsWorld->RemoveRigidBody(&m_rigidBody);
		return;
	}

	if (!map->GetMoveFloor2List().empty()) {
		parentWorldMatrix = map->MoveFloor2WorldMatrix(m_position);
		moveFloor2Position = map->GetMoveFloor2Position(m_position);
	}

	if (moveFloor2Find) {
		D3DXVECTOR3 toMoveFloor2Position = moveFloor2Position - m_position;
		float length = D3DXVec3Length(&toMoveFloor2Position);
		if (length <= 3.0f) {
			//���[���h���W�ɕϊ�����
			D3DXVec3TransformCoord(&m_position, &childPosition, &parentWorldMatrix);

			btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
			trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));

			//�e���猩���v���C���[�̍��W���X�V
			D3DXMATRIX worldMatrixInv;
			D3DXMatrixInverse(&worldMatrixInv, NULL, &parentWorldMatrix);
			D3DXVec3TransformCoord(&childPosition, &m_position, &worldMatrixInv);
		}
	}

	//�v���C���[�Ƃ̓����蔻��
	CollisionDetection();

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f });
}

void Spring::Render()
{
	m_model.SetDrawShadowMap(false, true);
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

void Spring::CollisionDetection()
{
	D3DXVECTOR3 toPlayerPos = player->GetPosition() - m_position;
	float length = D3DXVec3Length(&toPlayerPos);
	if (length <= 3.0f)
	{
		D3DXVECTOR3 toPlayerPosY = { 0.0f,toPlayerPos.y,0.0f };
		float lengthY = D3DXVec3Length(&toPlayerPosY);

		//Y�����ɓ�������
		if (toPlayerPosY.y >= 2.0f && lengthY <= 2.5f) {
			player->SetTreadOnSpring(true);

			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/Spring.wav");
			SE->Play(false);
		}
	}
}
