#include "stdafx.h"
#include "SkyBox.h"
#include "Scene/SceneManager.h"

SkyBox::SkyBox()
{
}

SkyBox::~SkyBox()
{
}

void SkyBox::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	HRESULT hr = D3DXCreateCubeTextureFromFile(
		g_pd3dDevice,
		"Assets/modelData/skyCubeMap.dds",
		&m_cubeMapTexture
	);
	if (FAILED(hr)) {
		MessageBox(NULL, "テクスチャのロードに失敗しました。キューブマップ", "エラー", MB_OK);
	}
	if (m_cubeMapTexture != NULL) {
		model.SetCubeMap(m_cubeMapTexture);
	}

	modelData.LoadModelData("Assets/modelData/sky.x", NULL);

	model.Init(&modelData);
	//ライトを初期化
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

	//衝突判定の初期化
	//スキンモデルからメッシュコライダーを作成する
	D3DXMATRIX* rootBoneMatrix = modelData.GetRootBoneWorldMatrix();
	meshCollider.CreateFromSkinModel(&model, rootBoneMatrix);

	//剛体を作るための情報を設定
	RigidBodyInfo rbInfo;
	rbInfo.collider = &meshCollider;		//剛体のコリジョンを設定する
	rbInfo.mass = 0.0f;					//質量を0にすると動かない剛体になる
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	//剛体を作成
	rigidBody.Create(rbInfo);

	//作成した剛体を物理ワールドに追加
	g_physicsWorld->AddRigidBody(&rigidBody);
}

bool SkyBox::Start()
{
	return true;
}

void SkyBox::Update()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		//剛体を削除
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}
}

void SkyBox::Render()
{
	model.SetDrawShadowMap(false, false);
	model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}
