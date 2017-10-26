#include "stdafx.h"
#include "MapChip.h"
#include "Scene/GameScene.h"
#include "myEngine/GameObject/GameObjectManager.h"

MapChip::MapChip()
{
}

MapChip::~MapChip()
{
	//剛体を削除
	g_physicsWorld->RemoveRigidBody(&rigidBody);
	//rigidBody.Release();
}

void MapChip::Init(const char* modelName, D3DXVECTOR3 position, D3DXQUATERNION rotation)
{
	//読み込むモデルのファイルパスを作成
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//モデルをロード
	modelData.LoadModelData(filePath, NULL);
	//ロードしたモデルデータを使ってSkinModelを初期化
	model.Init(&modelData);

	if (strcmp("Assets/modelData/skyBox.x", filePath) == 0) {
		//ライトを初期化
		light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
		light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
		light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
		light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

		light.SetDiffuseLightColor(0, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));
		light.SetDiffuseLightColor(1, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));
		light.SetDiffuseLightColor(2, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));
		light.SetDiffuseLightColor(3, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f));
		light.SetAmbientLight(D3DXVECTOR4(0.6f, 0.6f, 0.6f, 1.0f));
		model.SetLight(&light);
	}
	else {
		model.SetLight(&gameScene->GetLight());
	}

	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
	//衝突判定の初期化
	//スキンモデルからメッシュコライダーを作成する
	D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);
	//剛体の作成
	//剛体を作るための情報を設定
	RigidBodyInfo rbInfo;
	rbInfo.collider = &meshCollider;	//剛体のコリジョンを設定する
	rbInfo.mass = 0.0f;					//質量を0にすると動かない剛体になる
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	//剛体を作成
	rigidBody.Create(rbInfo);
	//作成した剛体を物理ワールドに追加
	g_physicsWorld->AddRigidBody(&rigidBody);
}

void MapChip::Update()
{
	if (gameScene == nullptr || gameScene->GetChengeStage()) {
		SetisDead();
		//剛体を削除
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}
}

void MapChip::Render()
{
	if (gameScene == nullptr) { return; }
	model.SetDrawShadowMap(false, true);
	model.Draw(&gameScene->GetGameCamera()->GetViewMatrix(), &gameScene->GetGameCamera()->GetViewProjectionMatrix());
}