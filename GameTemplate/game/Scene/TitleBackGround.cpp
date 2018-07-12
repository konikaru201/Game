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
	m_titleModel.SetLight(&m_light);

	m_rotation = { 0.0f,0.0f,0.0f,1.0f };
	D3DXQuaternionRotationAxis(&m_rotation, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXToRadian(-45.0f));
}

void TitleBackGround::Update()
{
	m_titleModel.UpdateWorldMatrix({ 0.0f, 6.0f, 21.0f }, m_rotation , { 1.0f, 1.0f, 1.0f });
}

void TitleBackGround::Render()
{
	m_titleModel.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

void TitleBackGround::RenderDepthValue()
{
	m_titleModel.SetDepthValueDraw(true);
	m_titleModel.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
	m_titleModel.SetDepthValueDraw(false);
}