#include "stdafx.h"
#include "Coin.h"
#include "Number/DisplayCoin.h"
#include "Scene/SceneManager.h"
#include "myEngine/Sound/SoundSource.h"

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

	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(2.0f, 2.0f, 2.0f, 1.0f));
	model.SetLight(&light);
	model.UpdateWorldMatrix(pos, rot, { 1.0f,1.0f,1.0f });

	position = pos;
	rotation = rot;
	InitPosition = pos;

	//影を描画するフラグを立てる
	SetRenderToShadow();
}

void Coin::Update()
{
	//シーン切り替え時に削除
	if (sceneManager->GetChangeSceneFlag()) {
		SetisDead();
		return;
	}

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
	if (length <= 0.9f && !flag)
	{
		flag = true;

		CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
		SE->Init("Assets/sound/coin.wav");
		SE->Play(false);
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
			int Count = 0;
			Count++;
			displayCoin->CoinCount(Count);
			SetisDead();
			return;
		}

		model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
	}
	else {
		model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
	}

	//テスト用
	//model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });

}

void Coin::Render()
{
	model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetViewProjectionMatrix());
}

void Coin::RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (gameCamera != nullptr) {
		model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		model.Draw(viewMatrix, projMatrix);
		model.SetDrawShadowMap(false, false);
	}
}