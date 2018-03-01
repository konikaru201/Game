#include "stdafx.h"
#include "StoneMonster.h"
#include "Scene/SceneManager.h"

StoneMonster::StoneMonster() :
	m_stoneMonsterStateMachine(this)
{
}

StoneMonster::~StoneMonster()
{
}

void StoneMonster::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	//���f���̏�����
	m_modelData.LoadModelData("Assets/modelData/StoneMonster.x", NULL);
	m_model.Init(&m_modelData);
	//���C�g��ݒ�
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

	m_model.UpdateWorldMatrix(pos, rot, { 1.0f,1.0f,1.0f });

	m_position = pos;
	m_rotation = rot;

	//���̂̍쐬
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(0.4f, 0.8f);

	//���̂̏���ݒ�
	RigidBodyInfo rbinfo;
	rbinfo.collider = coll;
	rbinfo.mass = 0.0f;
	rbinfo.pos = m_position;
	rbinfo.rot = m_rotation;
	//���̂��쐬
	m_rigidBody.Create(rbinfo);

	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));

	//�쐬�������̂𕨗����[���h�ɒǉ�
	g_physicsWorld->AddRigidBody(&m_rigidBody);
}

bool StoneMonster::Start()
{
	//�e��`�悷��t���O�𗧂Ă�
	SetRenderToShadow();

	goMgr->AddGameObject(&m_stoneMonsterStateMachine);

	return true;
}

void StoneMonster::Update()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		//���̂��폜
		g_physicsWorld->RemoveRigidBody(&m_rigidBody);
		return;
	}	

	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));

	m_model.UpdateWorldMatrix(m_position, m_rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));

}

void StoneMonster::Render()
{
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetViewProjectionMatrix());
}

void StoneMonster::RenderShadow(D3DXMATRIX * viewMatrix, D3DXMATRIX * projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (gameCamera != nullptr) {
		m_model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		m_model.Draw(viewMatrix, projMatrix);
		m_model.SetDrawShadowMap(false, false);
	}
}
