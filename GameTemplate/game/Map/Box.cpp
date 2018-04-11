#include "stdafx.h"
#include "Box.h"
#include "Scene/SceneManager.h"
#include "myEngine/Physics/CollisionAttr.h"
#include "myEngine/Timer/Timer.h"

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
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		//���̂��폜
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}

	
	switch (m_state)
	{
	case Box::Entity:
		m_timer += Timer::GetFrameDeltaTime();
		if (m_timer < ALPHA_TIME) {
			float t = m_timer / ALPHA_TIME;
			m_alpha = max(1.0f - t, 0.0f);
		}
		else {
			m_alpha = 0.0f;
			m_alphaTimer += Timer::GetFrameDeltaTime();
			if (m_alphaTimer >= 5.0f) {
				m_state = Clear;
				m_alphaTimer = 0.0f;
				m_timer = 0.0f;
			}
		}
		break;
	case Box::Clear:
		m_timer += Timer::GetFrameDeltaTime();
		if (m_timer < ALPHA_TIME) {
			float t = m_timer / ALPHA_TIME;
			m_alpha = min(t, 1.0f);
		}
		else {
			m_alpha = 1.0f;
			m_alphaTimer += Timer::GetFrameDeltaTime();
			if (m_alphaTimer >= 8.0f) {
				m_state = Entity;
				m_alphaTimer = 0.0f;
				m_timer = 0.0f;
			}
		}
		break;
	}

	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
}

void Box::Render()
{
}

void Box::PostRender()
{
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�����x��ݒ�
	model.SetAlpha(m_alpha);
	model.SetDrawShadowMap(false, true);
	model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());

	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
