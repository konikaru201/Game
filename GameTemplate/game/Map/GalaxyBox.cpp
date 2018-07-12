#include "stdafx.h"
#include "GalaxyBox.h"
#include "Scene/SceneManager.h"

GalaxyBox::GalaxyBox()
{
}

GalaxyBox::~GalaxyBox()
{
}

void GalaxyBox::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	HRESULT hr = D3DXCreateCubeTextureFromFile(
		g_pd3dDevice,
		"Assets/modelData/GalaxyCubeMap.dds",
		&m_cubeMapTexture
	);
	if (FAILED(hr)) {
		MessageBox(NULL, "テクスチャのロードに失敗しました。キューブマップ", "エラー", MB_OK);
	}
	if (m_cubeMapTexture != NULL) {
		m_model.SetCubeMap(m_cubeMapTexture);
	}

	m_modelData.LoadModelData("Assets/modelData/sky.x", NULL);

	m_model.Init(&m_modelData);
	//ライトを初期化
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
}

bool GalaxyBox::Start()
{
	return true;
}

void GalaxyBox::Update()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		return;
	}
}

void GalaxyBox::Render()
{
	m_model.SetDrawShadowMap(false, false);
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

void GalaxyBox::RenderDepthValue()
{
	m_model.SetDepthValueDraw(true);
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
	m_model.SetDepthValueDraw(false);
}