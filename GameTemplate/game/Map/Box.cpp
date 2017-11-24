#include "stdafx.h"
#include "Box.h"
#include "../Scene/GameScene.h"
#include "myEngine/Physics/CollisionAttr.h"

Box::Box()
{
}

Box::~Box()
{
}

void Box::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	modelData.LoadModelData("Assets/modelData/Box.x", NULL);
	model.Init(&modelData);
	model.SetLight(&gameScene->GetLight());
	model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0 }, { 1.0f,1.0f,1.0f });

	position = pos;
	rotation = rot;

	BoxCollider* boxCollider = new BoxCollider;
	boxCollider->Create(D3DXVECTOR3(2.5f, 2.5f, 2.5f));

	D3DXVECTOR3 rigidPos = position;
	rigidPos.y += 2.5f;

	//剛体の作成
	//剛体を作るための情報を設定
	RigidBodyInfo rbInfo;
	rbInfo.collider = boxCollider;	//剛体のコリジョンを設定する
	rbInfo.mass = 0.0f;				//質量を0にすると動かない剛体になる
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	//剛体を作成
	rigidBody.Create(rbInfo);
	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	//剛体の位置を更新。
	trans.setOrigin(btVector3(rigidPos.x, rigidPos.y, rigidPos.z));

	//rigidBody.GetBody()->setUserIndex(enCollisionAttr_Box);
	//rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	//rigidBody.GetBody()->setActivationState(DISABLE_DEACTIVATION);

	//作成した剛体を物理ワールドに追加
	g_physicsWorld->AddRigidBody(&rigidBody);
}

void Box::Update()
{
	if (gameScene == nullptr || gameScene->GetChengeStage()) {
		SetisDead();
		//剛体を削除
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}

	//if (g_player != nullptr) {
	//	if (g_player->GetIsOnBox() == true) {
	//		D3DXVECTOR3 playerPos = g_player->GetPosition();

	//		if (position.x - 2.5f < playerPos.x < position.x + 2.5f
	//			&& position.z + 2.5f < playerPos.z < position.z - 2.5f)
	//		{
	//			Hit = true;
	//		}
	//	}
	//}


	model.UpdateWorldMatrix(position, rotation, { 1.0f,1.0f,1.0f });
}

void Box::Render()
{
	if (gameScene == nullptr) { return; }
	model.SetDrawShadowMap(false, true);
	model.Draw(&gameScene->GetGameCamera()->GetViewMatrix(), &gameScene->GetGameCamera()->GetViewProjectionMatrix());
}
