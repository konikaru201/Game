#include "stdafx.h"
#include "Block.h"
#include "Scene/GameScene.h"
#include "myEngine/Physics/CollisionAttr.h"
#include "../Player/Player.h"

Block::Block()
{
}

Block::~Block()
{
}

void Block::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	modelData.LoadModelData("Assets/modelData/block.x", NULL);
	model.Init(&modelData);
	model.SetLight(&gameScene->GetLight());
	model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0 }, { 1.0f,1.0f,1.0f });

	position = pos;
	rotation = rot;

	D3DXMATRIX matrix;
	D3DXMatrixRotationQuaternion(&matrix, &rotation);
	rotationAxis.x = matrix.m[0][0];
	rotationAxis.y = matrix.m[0][1];
	rotationAxis.z = matrix.m[0][2];
	D3DXVec3Normalize(&rotationAxis, &rotationAxis);

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
	trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));

	rigidBody.GetBody()->setUserIndex(enCollisionAttr_Block);
	rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	rigidBody.GetBody()->setActivationState(DISABLE_DEACTIVATION);

	//作成した剛体を物理ワールドに追加
	g_physicsWorld->AddRigidBody(&rigidBody);
}

bool Block::Start()
{
	g_player->SetParentWorldMatrix(GetWorldMatrix());
	g_player->SetParentRotationMatrix(GetRotationMatrix());
	return true;
}

void Block::Update()
{
	if (gameScene == nullptr) {
		SetisDead();
		//剛体を削除
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}

	float angle = 0.3f * cPI / 180.0f;
	D3DXQUATERNION rot = { 0.0f,1.0f,0.0f,1.0f };
	D3DXQuaternionRotationAxis(&rot, &rotationAxis, angle);
	D3DXQuaternionMultiply(&rotation, &rotation, &rot);

	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));

	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });

	g_player->SetParentWorldMatrix(GetWorldMatrix());
	g_player->SetParentRotationMatrix(GetRotationMatrix());
}

void Block::Render()
{
	if (gameScene == nullptr) { return; }
	model.SetDrawShadowMap(false, true);
	model.Draw(&gameScene->GetGameCamera()->GetViewMatrix(), &gameScene->GetGameCamera()->GetViewProjectionMatrix());
}
