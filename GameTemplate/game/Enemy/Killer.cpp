#include "stdafx.h"
#include "Killer.h"
#include "Scene/GameScene.h"
#include "myEngine/Physics/CollisionAttr.h"

Killer::Killer()
{
}

Killer::~Killer()
{
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

	////剛体の作成
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(1.0f, 1.0f);
	characterController.Init(coll, position);
	characterController.SetGravity(0.0f);

	//剛体を作るための情報を設定
	RigidBodyInfo rbInfo;
	rbInfo.collider = coll;		//剛体のコリジョンを設定する
	rbInfo.mass = 0.0f;			//質量を0にすると動かない剛体になる
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	//剛体を作成
	rigidBody.Create(rbInfo);

	//作成した剛体を物理ワールドに追加
	g_physicsWorld->AddRigidBody(&rigidBody);

}

void Killer::Update()
{
	if (gameScene == nullptr || gameScene->GetChengeStage()) {
		SetisDead();
		//剛体を削除
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}

	//初期位置に戻す
	if (position.x < 55.0f || position.x > 130.0f
		|| position.z < -120.0f || position.z > -70.0f)
	{
		characterController.SetPosition(InitPosition);
		D3DXQuaternionRotationAxis(&rotation, &up, D3DXToRadian(-90.0f));
		state = State_Search;
	}

	D3DXVECTOR3 moveSpeed = Move();

	characterController.SetMoveSpeed(moveSpeed);
	characterController.Execute();
	position = characterController.GetPosition();

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
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };

	//プレイヤーの位置を取得
	D3DXVECTOR3 playerPos = g_player->GetPosition();
	D3DXVECTOR3 toPlayer = playerPos - position;
	//モデルのZ方向を取得
	D3DXVECTOR3 direction;
	D3DXMATRIX mWorld = model.GetWorldMatrix();
	direction.x = mWorld.m[2][0];
	direction.y = mWorld.m[2][1];
	direction.z = mWorld.m[2][2];

	float length = 0.0f;
	float angle = 0.0f;
	D3DXVECTOR3 AxisZ = { 0.0f,0.0f,1.0f };

	switch (state)
	{
	//探索状態
	case State_Search:
		length = D3DXVec3Length(&toPlayer);
		D3DXVec3Normalize(&toPlayer, &toPlayer);
		angle = D3DXVec3Dot(&toPlayer, &direction);
		angle = acos(angle);

		//発見された
		if (fabsf(angle) < D3DXToRadian(30.0f) && length < 12.0f) {
			state = State_Find;
		}

		move.x = -4.0f;

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
		move.y = 0.0f;

		//プレイヤーとの距離が離れる
		//又はプレイヤーにジャンプで避けられると見失う
		if (length > 30.0f || (position.y + 1.0f < playerPos.y && position.x < playerPos.x)) {
			state = State_Miss;
			break;
		}

		D3DXQuaternionRotationAxis(&rotation, &up, angle);
		break;
	//見失った状態
	case State_Miss:
		moveDir = direction * MoveSpeed;
		move = moveDir;
		break;
	default:
		break;
	}

	return move;
}