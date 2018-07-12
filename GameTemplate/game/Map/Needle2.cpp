#include "stdafx.h"
#include "Needle2.h"
#include "Scene/SceneManager.h"

Needle2::Needle2()
{
}

Needle2::~Needle2()
{
}

void Needle2::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation)
{
	m_modelData.LoadModelData("Assets/modelData/Needle2.x", NULL);
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
	m_model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });

	m_position = position;
	m_rotation = rotation;
}

bool Needle2::Start()
{
	//親のワールド行列を取得
	m_parentWorldMatrix = map->GetEarthInstance()->GetWorldMatrix();
	//親のワールド行列から逆行列を作成
	D3DXMATRIX parentWorldMatrixInv;
	D3DXMatrixInverse(&parentWorldMatrixInv, NULL, &m_parentWorldMatrix);
	D3DXVec3TransformCoord(&m_childPosition, &m_position, &parentWorldMatrixInv);
	//親のワールド行列からクォータニオンを作成
	D3DXQUATERNION parentRotationMatrixInv;
	D3DXQuaternionRotationMatrix(&parentRotationMatrixInv, &parentWorldMatrixInv);
	//親から見たクォータニオンに変換
	D3DXQuaternionMultiply(&m_childRotation, &m_rotation, &parentRotationMatrixInv);

	return true;
}

void Needle2::Update()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		return;
	}

	//親のワールド行列を取得
	m_parentWorldMatrix = map->GetEarthInstance()->GetWorldMatrix();
	//ワールド座標に変換する
	D3DXVec3TransformCoord(&m_position, &m_childPosition, &m_parentWorldMatrix);
	//親のワールド行列から逆行列を作成
	D3DXMATRIX parentWorldMatrixInv;
	D3DXMatrixInverse(&parentWorldMatrixInv, NULL, &m_parentWorldMatrix);
	D3DXVec3TransformCoord(&m_childPosition, &m_position, &parentWorldMatrixInv);

	D3DXVECTOR3 toEarthPos = m_position - map->GetEarthInstance()->GetPosition();
	D3DXVec3Normalize(&toEarthPos, &toEarthPos);
	m_position += toEarthPos * m_moveSpeed * m_timer;
	if (m_timer <= 0.0f) {
		m_timer = 0.0f;
		m_upFlag = true;
	}
	else if (m_timer >= 0.5f) {
		m_timer = 0.5f;
		m_upFlag = false;
	}

	if (m_upFlag) {
		m_timer += Timer::GetFrameDeltaTime();
	}
	else {
		m_timer -= Timer::GetFrameDeltaTime();
	}

	//親のワールド行列からクォータニオンを作成
	D3DXQUATERNION parentRotation;
	D3DXQuaternionRotationMatrix(&parentRotation, &m_parentWorldMatrix);
	//親のクォータニオンを使って回転させる
	D3DXQuaternionMultiply(&m_rotation, &m_childRotation, &parentRotation);
	//親のワールド行列の逆行列からクォータニオンを作成
	D3DXQUATERNION parentRotationMatrixInv;
	D3DXQuaternionRotationMatrix(&parentRotationMatrixInv, &parentWorldMatrixInv);
	//親から見たクォータニオンに変換
	D3DXQuaternionMultiply(&m_childRotation, &m_rotation, &parentRotationMatrixInv);

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f });
}

void Needle2::Render()
{
	m_model.SetDrawShadowMap(false, false);
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

void Needle2::RenderShadow(D3DXMATRIX * viewMatrix, D3DXMATRIX * projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (gameCamera != nullptr) {
		m_model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		m_model.Draw(viewMatrix, projMatrix);
		m_model.SetDrawShadowMap(false, false);
	}
}

void Needle2::RenderDepthValue()
{
	m_model.SetDepthValueDraw(true);
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
	m_model.SetDepthValueDraw(false);
}