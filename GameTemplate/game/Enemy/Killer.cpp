#include "stdafx.h"
#include "Killer.h"
#include "Scene/SceneManager.h"
#include "myEngine/Physics/CollisionAttr.h"
#include "myEngine/Timer/Timer.h"

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
	//ライトを設定
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

	model.UpdateWorldMatrix( pos, rot, { 1.0f,1.0f,1.0f });

	position = pos;
	rotation = rot;
	InitPosition = pos;

	//移動限界ラインを設定
	moveLimitLine[0] = 55.0f;
	moveLimitLine[1] = 130.0f;
	moveLimitLine[2] = -70.0f;
	moveLimitLine[3] = -120.0f;

	state = State_Search;

	////剛体の作成
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(0.8f, 1.0f);

	//剛体を作るための情報を設定
	RigidBodyInfo rbInfo;
	rbInfo.collider = coll;		//剛体のコリジョンを設定する
	rbInfo.mass = 0.0f;			//質量を0にすると動かない剛体になる
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	//剛体を作成
	rigidBody.Create(rbInfo);

	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(position.x, position.y, position.z));

	//作成した剛体を物理ワールドに追加
	g_physicsWorld->AddRigidBody(&rigidBody);

}

void Killer::Update()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		//剛体を削除
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}
	//if (gameScene == nullptr || isDead) {
	//	SetisDead();
	//	//剛体を削除
	//	g_physicsWorld->RemoveRigidBody(&rigidBody);
	//	return;
	//}

	//初期位置に戻す
	if (position.x < moveLimitLine[0] || position.x > moveLimitLine[1]
		|| position.z < moveLimitLine[3] || position.z > moveLimitLine[2])
	{
		position = InitPosition;
		D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(-90.0f));
		state = State_Search;
	}

	D3DXVECTOR3 moveSpeed = Move();
	position += moveSpeed / 60.0f;

	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(position.x, position.y, position.z));

	model.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Killer::Render()
{
	model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetViewProjectionMatrix());
}

D3DXVECTOR3 Killer::Move()
{
	//移動速度を取得
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };

	//プレイヤーの位置を取得
	D3DXVECTOR3 playerPos = player->GetPosition();
	D3DXVECTOR3 toPlayer = playerPos - position;
	//モデルのZ方向を取得
	D3DXVECTOR3 direction;
	D3DXMATRIX mWorld = model.GetWorldMatrix();
	direction.x = mWorld.m[2][0];
	direction.y = mWorld.m[2][1];
	direction.z = mWorld.m[2][2];

	float length = D3DXVec3Length(&toPlayer);
	float angle = 0.0f;
	D3DXVECTOR3 AxisZ = { 0.0f,0.0f,1.0f };

	//プレイヤーとの当たり判定
	CollisionDetection(length, toPlayer);

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

		move.x = -moveSpeed;

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

		//プレイヤーとの距離が離れる
		//又はプレイヤーにジャンプで避けられると見失う
		if (length > 30.0f || (position.y + 1.0f < playerPos.y && position.x < playerPos.x)) {
			state = State_Miss;
			break;
		}

		D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);

		direction *= moveSpeed;
		move = direction;
		move.y = 0.0f;

		break;
	//見失った状態
	case State_Miss:
		moveDir = direction * moveSpeed;
		move = moveDir;
		break;
	//死亡状態
	case State_Dead:
		timer += Timer::GetFrameDeltaTime();
		move = { 0.0f, -moveSpeed * (timer + 1.0f), 0.0f };
		if (timer > 5.0f) {
			isDead = true;
			timer = 0.0f;
		}
		break;
	//プレイヤーにヒットした状態
	case State_Hit:
		timer += Timer::GetFrameDeltaTime();
		move = { 0.0f,0.0f,0.0f };
		if (timer > 5.0f) {
			isDead = true;
			timer = 0.0f;
		}
		break;
	}

	return move;
}

void Killer::CollisionDetection(float Length, const D3DXVECTOR3& ToPlayer)
{
	//プレイヤーとの距離が近ければ自身かプレイヤーの死亡フラグを立てる
	if (Length <= 1.5f) {
		D3DXVECTOR3 toPlayerX = { ToPlayer.x,0.0f,0.0f };
		float lengthX = D3DXVec3Length(&toPlayerX);

		D3DXVECTOR3 toPlayerY = { 0.0f,ToPlayer.y,0.0f };
		float lengthY = D3DXVec3Length(&toPlayerY);

		D3DXVECTOR3 toPlayerZ = { 0.0f,0.0f,ToPlayer.z };
		float lengthZ = D3DXVec3Length(&toPlayerZ);

		//Y方向に当たった
		if (toPlayerY.y > 0.0f && lengthY <= 1.3f) {
			//キラーが死亡
			player->SetTreadOnEnemy(true);
			state = State_Dead;
		}
		//X方向に当たった
		else if (lengthY <= 0.5f && lengthX <= 1.5f) {
			////プレイヤーが死亡
			m_hitPlayer = true;
			player->SetHitEnemy(m_hitPlayer);
			state = State_Hit;
		}
		//Z方向に当たった
		else if (lengthY <= 0.5f && lengthZ <= 0.5f) {
			//プレイヤーが死亡
			m_hitPlayer = true;
			player->SetHitEnemy(m_hitPlayer);
			state = State_Hit;
		}
	}

}