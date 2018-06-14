#include "stdafx.h"
#include "Earth.h"
#include "Scene/SceneManager.h"

Earth::Earth()
{
}

Earth::~Earth()
{
}

void Earth::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation)
{
	m_modelData.LoadModelData("Assets/modelData/earth.x", NULL);
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
	m_model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0 }, { 1.0f,1.0f,1.0f });

	m_position = position;
	m_rotation = rotation;

	//衝突判定の初期化
	//スキンモデルからメッシュコライダーを作成する
	D3DXMATRIX* rootBoneMatrix = m_modelData.GetRootBoneWorldMatrix();
	m_meshCollider.CreateFromSkinModel(&m_model, rootBoneMatrix);

	//剛体を作るための情報を設定
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider;		//剛体のコリジョンを設定する
	rbInfo.mass = 0.0f;					//質量を0にすると動かない剛体になる
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	//剛体を作成
	m_rigidBody.Create(rbInfo);

	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
	trans.setRotation(btQuaternion(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w));

	//作成した剛体を物理ワールドに追加
	g_physicsWorld->AddRigidBody(&m_rigidBody);
}

bool Earth::Start()
{
	return true;
}

void Earth::Update()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		//剛体を削除
		g_physicsWorld->RemoveRigidBody(&m_rigidBody);
		return;
	}

	m_isRotate = false;
	if ((pad->GetLStickXF() != 0.0f || pad->GetLStickYF() != 0.0f)) {
		D3DXVECTOR3 rotationAxis = { 0.0f,1.0f,0.0f };
		D3DXVECTOR3 stickDir;
		stickDir.y = 0.0f;
		stickDir.x = pad->GetLStickXF();
		stickDir.z = pad->GetLStickYF();
		D3DXVec3Normalize(&stickDir, &stickDir);
		
		float angle = -0.3f * cPI / 180.0f;

		D3DXVECTOR3 Cross;
		D3DXVec3Cross(&Cross, &stickDir, &rotationAxis);

		D3DXQUATERNION rot;
		D3DXQuaternionIdentity(&rot);
		D3DXQuaternionRotationAxis(&rot, &Cross, angle);
		D3DXQuaternionMultiply(&m_rotation, &m_rotation, &rot);

		m_isRotate = true;
	}

	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	trans.setRotation(btQuaternion(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w));

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f });
}

void Earth::Render()
{
	m_model.SetDrawShadowMap(false, true);
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}
