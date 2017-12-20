#include "stdafx.h"
#include "Coin.h"
#include "Scene/GameScene.h"

Coin::Coin()
{
}

Coin::~Coin()
{
}

void Coin::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	//���f���̏�����
	modelData.LoadModelData("Assets/modelData/Coin.x", NULL);
	model.Init(&modelData);

	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	model.SetLight(&light);
	model.UpdateWorldMatrix(pos, rot, { 1.0f,1.0f,1.0f });

	position = pos;
	rotation = rot;
	InitPosition = pos;
}

void Coin::Update()
{
	if (gameScene == nullptr || gameScene->GetChengeStage())
	{
		SetisDead();
		return;
	}

	float angle = 1.0f * cPI / 180.0f;
	D3DXQUATERNION rot = { 0.0f,1.0f,0.0f,1.0f };
	D3DXVECTOR3 up = { 0.0f,1.0f,0.0f };
	D3DXQuaternionRotationAxis(&rot, &up, angle);
	D3DXQuaternionMultiply(&rotation, &rotation, &rot);

	//�v���C���[�Ƃ̋��������߂�
	D3DXVECTOR3 PlayerPos = g_player->GetPosition();
	D3DXVECTOR3 toPlayer = position - PlayerPos;
	float length = D3DXVec3Length(&toPlayer);
	//�v���C���[�Ƌ������߂���Ζ������J�E���g���č폜
	if (length <= 0.7f)
	{
		flag = true;
	}

	if (flag)
	{
		float angle = 30.0f * cPI / 180.0f;
		D3DXQUATERNION rot = { 0.0f,1.0f,0.0f,1.0f };
		D3DXVECTOR3 up = { 0.0f,1.0f,0.0f };
		D3DXQuaternionRotationAxis(&rot, &up, angle);
		D3DXQuaternionMultiply(&rotation, &rotation, &rot);

		position.y += moveSpeed;

		if (position.y - InitPosition.y >= 1.0f) {
			int Count = g_player->GetCoinCount();
			Count++;
			g_player->SetCoinCount(Count);
			SetisDead();
			return;
		}

		model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
	}
	else {
		model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
	}
}

void Coin::Render()
{
	if (gameScene == nullptr){	return; }
	model.Draw(&gameScene->GetGameCamera()->GetViewMatrix(), &gameScene->GetGameCamera()->GetViewProjectionMatrix());
}

//void Coin::RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
//{
//	if (g_coin != nullptr) {
//		model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
//		model.Draw(viewMatrix, projMatrix);
//		model.SetDrawShadowMap(false, false);
//	}
//}