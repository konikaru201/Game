#include "stdafx.h"
#include "MoveFloor2.h"
#include "Scene/SceneManager.h"
#include "myEngine/Physics/CollisionAttr.h"
#include "myEngine/Timer/Timer.h"

MoveFloor2* g_moveFloor2;

MoveFloor2::MoveFloor2()
{
}

MoveFloor2::~MoveFloor2()
{
	//g_physicsWorld->RemoveRigidBody(&rigidBody);
	//rigidBody.Release();
}

void MoveFloor2::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	modelData.LoadModelData("Assets/modelData/MoveFloor_2.x", NULL);
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

	model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0 }, { 1.0f,1.0f,1.0f });

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

	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(position.x, position.y, position.z));

	rigidBody.GetBody()->setUserIndex(enCollisionAttr_MoveFloor2);
	rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	rigidBody.GetBody()->setActivationState(DISABLE_DEACTIVATION);

	//作成した剛体を物理ワールドに追加
	g_physicsWorld->AddRigidBody(&rigidBody);
}

void MoveFloor2::Update()
{
	
}
void MoveFloor2::PreUpdate()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		//剛体を削除
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}
	//if (gameScene == nullptr) {
	//	SetisDead();
	//	g_moveFloor2 = nullptr;
	//	//剛体を削除
	//	g_physicsWorld->RemoveRigidBody(&rigidBody);
	//	return;
	//}

	Move();

	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(position.x, position.y, position.z));

	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
}
void MoveFloor2::Move()
{
	Timer += Timer::GetFrameDeltaTime();
	moveFlg = true;
	if (Timer >= 7.0f) {
		moveSpeed *= -1.0f;
		Timer = 0.0f;
	}
	if (Timer >= 2.0f)
	{
		position += moveSpeed;
	}
	else
	{
		moveFlg = false;
	}
}

void MoveFloor2::Render()
{
	model.SetDrawShadowMap(false, true);
	model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetViewProjectionMatrix());
}