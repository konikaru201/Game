#include "stdafx.h"
#include "Star.h"
#include "Scene/SceneManager.h"
#include "myEngine/Timer/Timer.h"

Star::Star()
{
}

Star::~Star()
{
}

void Star::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	//モデルの初期化
	m_modelData.LoadModelData("Assets/modelData/Star.x", NULL);
	m_model.Init(&m_modelData);
	//ライトの設定
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetAmbientLight(D3DXVECTOR4(2.0f, 2.0f, 2.0f, 1.0f));
	m_model.SetLight(&m_light);
	m_model.UpdateWorldMatrix(pos, rot, { 1.0f,1.0f,1.0f });

	m_position = pos;
	m_rotation = rot;
	m_initPosition = pos;

	//影を描画するフラグを立てる
	SetRenderToShadow();
}

void Star::Update()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		return;
	}

	float angle = 1.0f * cPI / 180.0f;
	D3DXQUATERNION rot = { 0.0f,1.0f,0.0f,1.0f };
	D3DXVECTOR3 up = { 0.0f,1.0f,0.0f };
	D3DXQuaternionRotationAxis(&rot, &up, angle);
	D3DXQuaternionMultiply(&m_rotation, &m_rotation, &rot);

	//プレイヤーとの距離を求める
	D3DXVECTOR3 PlayerPos = player->GetPosition();
	D3DXVECTOR3 toPlayer = m_position - PlayerPos;
	float length = D3DXVec3Length(&toPlayer);
	//プレイヤーと距離が近ければ枚数をカウントして削除
	if (length <= 1.0f)
	{
		m_flag = true;
		player->SetGetStar(m_flag);
	}

	if (m_flag)
	{
		float angle = 30.0f * cPI / 180.0f;
		D3DXQUATERNION rot = { 0.0f,1.0f,0.0f,1.0f };
		D3DXVECTOR3 up = { 0.0f,1.0f,0.0f };
		D3DXQuaternionRotationAxis(&rot, &up, angle);
		D3DXQuaternionMultiply(&m_rotation, &m_rotation, &rot);

		m_timer += Timer::GetFrameDeltaTime();
		if (m_timer > 3.0f) {
			m_flag = false;
		}

		m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f });
	}
	else {
		m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f });
	}
}

void Star::Render()
{
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

void Star::RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (gameCamera != nullptr) {
		m_model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		m_model.Draw(viewMatrix, projMatrix);
		m_model.SetDrawShadowMap(false, false);
	}
}
