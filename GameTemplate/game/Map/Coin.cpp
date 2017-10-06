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
	//モデルの初期化
	modelData.LoadModelData("Assets/modelData/Coin.x", NULL);
	model.Init(&modelData);
	model.SetLight(&gameScene->GetLight());
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

	//プレイヤーとの距離を求める
	D3DXVECTOR3 PlayerPos = gameScene->GetPlayer()->GetPosition();
	D3DXVECTOR3 toPlayer = position - PlayerPos;
	float length = D3DXVec3Length(&toPlayer);
	//プレイヤーと距離が近ければ枚数をカウントして削除
	if (length <= 0.5f)
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
			int Count = gameScene->GetPlayer()->GetCoinCount();
			Count++;
			gameScene->GetPlayer()->SetCoinCount(Count);
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