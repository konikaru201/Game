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
	modelData.LoadModelData("Assets/modelData/Star.x", NULL);
	model.Init(&modelData);
	//ライトの設定
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
	model.UpdateWorldMatrix(pos, rot, { 1.0f,1.0f,1.0f });

	position = pos;
	rotation = rot;
	InitPosition = pos;
}

void Star::Update()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		return;
	}
	//if (gameScene == nullptr)
	//{
	//	SetisDead();
	//	return;
	//}

	float angle = 1.0f * cPI / 180.0f;
	D3DXQUATERNION rot = { 0.0f,1.0f,0.0f,1.0f };
	D3DXVECTOR3 up = { 0.0f,1.0f,0.0f };
	D3DXQuaternionRotationAxis(&rot, &up, angle);
	D3DXQuaternionMultiply(&rotation, &rotation, &rot);

	//プレイヤーとの距離を求める
	D3DXVECTOR3 PlayerPos = player->GetPosition();
	D3DXVECTOR3 toPlayer = position - PlayerPos;
	float length = D3DXVec3Length(&toPlayer);
	//プレイヤーと距離が近ければ枚数をカウントして削除
	if (length <= 0.7f)
	{
		flag = true;
		player->SetGetStar(flag);
	}

	if (flag)
	{
		float angle = 30.0f * cPI / 180.0f;
		D3DXQUATERNION rot = { 0.0f,1.0f,0.0f,1.0f };
		D3DXVECTOR3 up = { 0.0f,1.0f,0.0f };
		D3DXQuaternionRotationAxis(&rot, &up, angle);
		D3DXQuaternionMultiply(&rotation, &rotation, &rot);

		timer += Timer::GetFrameDeltaTime();
		if (timer > 3.0f) {
			flag = false;
		}

		model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
	}
	else {
		model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
	}
}

void Star::Render()
{
	model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetViewProjectionMatrix());
}
