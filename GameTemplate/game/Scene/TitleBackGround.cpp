#include "stdafx.h"
#include "TitleBackGround.h"
#include "SceneManager.h"
#include "myEngine/GameObject/GameObjectManager.h"

TitleBackGround::TitleBackGround()
{
}

TitleBackGround::~TitleBackGround()
{
}

void TitleBackGround::Init()
{
	m_backGround = std::make_unique<Sprite>();
	m_backGround->Initialize("Assets/sprite/Title.png");

	m_modelData.LoadModelData("Assets/modelData/Unity.x", &m_animation);
	m_model.Init(&m_modelData);
	m_titleModelData.LoadModelData("Assets/modelData/Title.x", NULL);
	m_titleModel.Init(&m_titleModelData);
	//ƒ‰ƒCƒg‚ðÝ’è
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
	m_titleModel.SetLight(&m_light);

	m_position = { 0.0f,-1.5f,0.0f };
	m_rotation = { 0.0f,0.0f,0.0f,1.0f };
	D3DXQuaternionRotationAxis(&m_rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(-90.0f));

	m_titlePosition = { -2.0f, 1.0f, -2.0f };
	m_titleRotation = { 0.0f,0.0f,0.0f,1.0f };

	m_animation.SetAnimationEndTime(m_animationRun, 0.8f);
	m_animation.PlayAnimation(m_animationRun);

	gameCamera = goMgr->NewGameObject<GameCamera>();
}

void TitleBackGround::Update()
{
	gameCamera->SetPosition(D3DXVECTOR3(-2.0f, 0.0f, 5.0f));
	gameCamera->SetTarget(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));

	m_animation.Update(1.0f / 60.0f);

	m_model.UpdateWorldMatrix(m_position, m_rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	m_titleModel.UpdateWorldMatrix(m_titlePosition, m_titleRotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void TitleBackGround::Render()
{
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_backGround->Render();
	g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	m_titleModel.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

void TitleBackGround::Release()
{
	gameCamera->SetisDead();
	gameCamera = nullptr;
}
