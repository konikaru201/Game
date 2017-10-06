#include "stdafx.h"
#include "Killer.h"
#include "Scene/GameScene.h"
#include "myEngine/Physics/CollisionAttr.h"

Killer::Killer()
{
}

Killer::~Killer()
{
	//characterController.RemoveRigidBoby();
	//characterController.~CharacterController();
}

void Killer::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	//モデルの初期化
	modelData.LoadModelData("Assets/modelData/Killer.x", NULL);
	model.Init(&modelData);
	model.SetLight(&gameScene->GetLight());
	model.UpdateWorldMatrix( pos, rot, { 1.0f,1.0f,1.0f });

	position = pos;
	rotation = rot;
	InitPosition = pos;

	state = State_Search;

	//剛体の作成
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(1.0f, 1.0f);
	characterController.Init(coll, position);

	characterController.GetRigidBody()->GetBody()->setUserIndex(enCollisionAttr_Killer);
}

void Killer::Update()
{
	if (gameScene == nullptr || gameScene->GetChengeStage()) {
		SetisDead();
		//剛体を削除
		characterController.RemoveRigidBoby();
		return;
	}

	//移動速度を設定
	characterController.SetMoveSpeed(Move());
	//キャラクターコントローラーを実行
	characterController.Execute();
	//座標を設定
	position = characterController.GetPosition();

	//初期位置に戻す
	if (position.z >= -40.0f)
	{
		position = InitPosition;
		characterController.SetPosition(position);
	}

	model.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Killer::Render()
{
	if (gameScene == nullptr) { return; }
	model.Draw(&gameScene->GetGameCamera()->GetViewMatrix(), &gameScene->GetGameCamera()->GetViewProjectionMatrix());
}

D3DXVECTOR3 Killer::Move()
{
	//移動速度を取得
	D3DXVECTOR3 move = characterController.GetMoveSpeed();

	//プレイヤーの位置を取得
	D3DXVECTOR3 toPlayer = gameScene->GetPlayer()->GetPosition() - position;
	//モデルのZ方向を取得
	D3DXVECTOR3 direction;
	D3DXMATRIX mWorld = model.GetWorldMatrix();
	direction.x = mWorld.m[2][0];
	direction.y = mWorld.m[2][1];
	direction.z = mWorld.m[2][2];

	float length = 0.0f;
	float angle = 0.0f;
	D3DXVECTOR3 AxisZ = { 0.0f,0.0f,1.0f };
	D3DXVECTOR3 up = { 0.0f,1.0f,0.0f };
	switch (state)
	{
	//探索状態
	case State_Search:
		length = D3DXVec3Length(&toPlayer);
		D3DXVec3Normalize(&toPlayer, &toPlayer);
		angle = D3DXVec3Dot(&toPlayer, &direction);
		angle = acos(angle);

		//発見された
		if (fabsf(angle) < D3DXToRadian(45.0f) && length < 5.0f) {
			state = State_Find;
		}

		move.z = 2.0f;

		break;
	//発見状態
	case State_Find:
		length = D3DXVec3Length(&toPlayer);
		D3DXVec3Normalize(&toPlayer, &toPlayer);
		angle = D3DXVec3Dot(&toPlayer, &AxisZ);
		angle = acos(angle);
		if (toPlayer.x <= 0.0f) {
			angle *= -1.0f;
		}
		D3DXVec3Scale(&toPlayer, &toPlayer, MoveSpeed);
		move = toPlayer;
		
		D3DXQuaternionRotationAxis(&rotation, &up, angle);
		break;
	default:
		break;
	}

	return move;
}