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

void Coin::Init(int numInstancing)
{
	//モデルの初期化
	model.SetInstancingDraw(true);
	m_numInstancing = numInstancing;
	//インスタンシング描画する数を設定
	model.SetNumInstancing(m_numInstancing);
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
	model.UpdateWorldMatrix({ 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f,1.0f }, { 1.0f,1.0f,1.0f });

	scale = { 0.06f,0.06f,0.06f };
	
	//影を描画するフラグを立てる
	SetRenderToShadow();

	//インスタンシング描画用のワールド行列を初期化
	InitInstancingWorldMatrix();
}

bool Coin::Start()
{

	return true;
}

void Coin::Update()
{
	//シーン切り替え時に削除
	if (sceneManager->GetChangeSceneFlag()) {
		SetisDead();
		m_coinInfoList.clear();
		return;
	}

	UpdateInstancingWorldMatrix();
}

void Coin::Render()
{
	model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

void Coin::RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (gameCamera != nullptr) {
		model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		model.Draw(viewMatrix, projMatrix);
		model.SetDrawShadowMap(false, false);
	}
}

void Coin::InitInstancingWorldMatrix()
{
	int index = 0;
	for (auto& coinInfo : m_coinInfoList) {
		D3DXVECTOR3 pos = coinInfo.position;
		D3DXQUATERNION rot = coinInfo.rotation;
		//ワールド行列の計算
		D3DXMATRIX mTrans, mScale, mRotationMatrix;
		D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.z);
		D3DXMatrixTranslation(&mTrans, pos.x, pos.y, pos.z);
		D3DXMatrixRotationQuaternion(&mRotationMatrix, &rot);

		IWorldMatrix[index] = mScale * mRotationMatrix * mTrans;
		index++;
	}
}

void Coin::UpdateInstancingWorldMatrix()
{
	std::list<CoinInfo>::iterator it;

	int index = 0;
	for (it = m_coinInfoList.begin(); it != m_coinInfoList.end(); ++it) {
		D3DXVECTOR3 position = (it)->position;
		D3DXQUATERNION rotation = (it)->rotation;
		//回転を計算
		float angle = 1.0f * cPI / 180.0f;
		D3DXQUATERNION rot = { 0.0f,1.0f,0.0f,1.0f };
		D3DXVECTOR3 up = { 0.0f,1.0f,0.0f };
		D3DXQuaternionRotationAxis(&rot, &up, angle);
		D3DXQuaternionMultiply(&rotation, &rotation, &rot);
		//回転を更新
		(it)->rotation = rotation;

		//プレイヤーとの距離を求める
		D3DXVECTOR3 PlayerPos = player->GetPosition();
		D3DXVECTOR3 toPlayer = position - PlayerPos;
		float length = D3DXVec3Length(&toPlayer);
		if (length <= 0.9f) {
			//コインの枚数をカウント
			CoinUI->CoinCount();
			it = m_coinInfoList.erase(it);
			m_numInstancing--;
			//音を鳴らす
			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/coin.wav");
			SE->Play(false);

			return;
		}

		//ワールド行列の計算
		D3DXMATRIX mTrans, mScale, mRotationMatrix;
		D3DXMatrixScaling(&mScale, scale.x, scale.y, scale.z);
		D3DXMatrixTranslation(&mTrans, position.x, position.y, position.z);
		D3DXMatrixRotationQuaternion(&mRotationMatrix, &rotation);

		IWorldMatrix[index] = mScale * mRotationMatrix * mTrans;
		index++;
	}

	model.SetNumInstancing(m_numInstancing);
}
