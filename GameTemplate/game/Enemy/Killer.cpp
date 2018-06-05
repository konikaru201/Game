#include "stdafx.h"
#include "Killer.h"
#include "Scene/SceneManager.h"
#include "myEngine/Physics/CollisionAttr.h"
#include "myEngine/Timer/Timer.h"
#include "myEngine/Sound/SoundSource.h"

Killer::Killer()
{
}

Killer::~Killer()
{
}

void Killer::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	//モデルの初期化
	m_modelData.LoadModelData("Assets/modelData/Killer.x", NULL);
	m_model.Init(&m_modelData);
	//ライトを設定
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

	m_model.UpdateWorldMatrix( pos, rot, { 1.0f,1.0f,1.0f });

	m_position = pos;
	m_rotation = rot;
	m_initPosition = pos;
	m_initRotation = rot;

	//移動限界ラインを設定
	m_moveLimitLine[0] = m_position.x + -80.0f;	//左
	m_moveLimitLine[1] = m_position.x + 80.0f;	//右		
	m_moveLimitLine[2] = m_position.z + 80.0f;	//前
	m_moveLimitLine[3] = m_position.z + -80.0f;	//後

	m_state = State_Search;

	////剛体の作成
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(0.8f, 1.0f);

	//剛体を作るための情報を設定
	RigidBodyInfo rbInfo;
	rbInfo.collider = coll;		//剛体のコリジョンを設定する
	rbInfo.mass = 0.0f;			//質量を0にすると動かない剛体になる
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	//剛体を作成
	m_rigidBody.Create(rbInfo);

	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));

	//作成した剛体を物理ワールドに追加
	g_physicsWorld->AddRigidBody(&m_rigidBody);

	//影を描画するフラグを立てる
	SetRenderToShadow();

	////パーティクルの初期化
	//SParticleEmitParameter param;
	//param.texturePath = "Assets/sprite/smoke.png";
	//param.w = 0.5f;
	//param.h = 0.5f;
	//param.intervalTime = 0.1f;
	//param.initSpeed = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	//param.position = position;
	//param.alpha = 1.0f;
	//particleEmitter.Init(param);
}

void Killer::Update()
{
	if (sceneManager->GetChangeSceneFlag() || m_isDead)
	{
		SetisDead();
		//剛体を削除
		g_physicsWorld->RemoveRigidBody(&m_rigidBody);
		return;
	}

	//初期位置に戻す
	if (m_position.x < m_moveLimitLine[0] || m_position.x > m_moveLimitLine[1]
		|| m_position.z < m_moveLimitLine[3] || m_position.z > m_moveLimitLine[2]
		|| m_isRespawn)
	{
		SetisDead();
		g_physicsWorld->RemoveRigidBody(&m_rigidBody);

		Killer* killer = goMgr->NewGameObject<Killer>();
		killer->Init(m_initPosition,m_initRotation);
	}

	D3DXVECTOR3 moveSpeed = Move();
	m_position += moveSpeed / 60.0f;

	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));

	m_model.UpdateWorldMatrix(m_position, m_rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Killer::Render()
{
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

D3DXVECTOR3 Killer::Move()
{
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };

	//プレイヤーの位置を取得
	D3DXVECTOR3 playerPos = player->GetPosition();
	D3DXVECTOR3 toPlayer = playerPos - m_position;
	//モデルのZ方向を取得
	D3DXVECTOR3 direction;
	D3DXMATRIX mWorld = m_model.GetWorldMatrix();
	direction.x = mWorld.m[2][0];
	direction.y = mWorld.m[2][1];
	direction.z = mWorld.m[2][2];

	float length = D3DXVec3Length(&toPlayer);
	float angle = 0.0f;
	D3DXQUATERNION rot;
	D3DXQuaternionIdentity(&rot);
	D3DXVECTOR3 Cross;

	//プレイヤーとの当たり判定
	CollisionDetection(length, toPlayer);

	//particleEmitter.SetSpeed(GetDirection() * -1.0f);
	//particleEmitter.SetPosition(position);
	//particleEmitter.Update();

	//プレイヤーがステージクリアしたらそのまま直進
	if(player->GetStar()){
		m_state = State_Miss;
	}

	switch (m_state)
	{
	//探索状態
	case State_Search:
		length = D3DXVec3Length(&toPlayer);
		D3DXVec3Normalize(&toPlayer, &toPlayer);
		angle = D3DXVec3Dot(&toPlayer, &direction);
		angle = acosf(angle);

		//発見された
		if (fabsf(angle) < D3DXToRadian(30.0f) && length < 12.0f) {
			m_state = State_Find;
		}

		move = direction * m_moveSpeed;
		//move.x = direction.x * moveSpeed;

		break;
	//発見状態
	case State_Find:
		//プレイヤーとの距離が離れる
		//又はプレイヤーにジャンプで避けられると見失う
		if (length > 30.0f || (m_position.y + 1.0f < playerPos.y && m_position.x < playerPos.x)) {
			m_state = State_Miss;
			break;
		}

		D3DXVec3Normalize(&toPlayer, &toPlayer);
		angle = D3DXVec3Dot(&toPlayer, &direction);
		if (angle > 1.0f) {
			angle = 1.0f;
		}
		else if(angle < -1.0f){
			angle = -1.0f;
		}
		angle = acosf(angle);
		D3DXVec3Cross(&Cross, &toPlayer, &direction);
		if (Cross.y > 0.0f) {
			angle *= -1.0f;
		}

		angle /= 30;
		D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);
		D3DXQuaternionMultiply(&m_rotation, &m_rotation, &rot);

		direction *= m_moveSpeed;
		move = direction;
		move.y = 0.0f;

		break;
	//見失った状態
	case State_Miss:
		m_moveDir = direction * m_moveSpeed;
		move = m_moveDir;
		break;
	//死亡状態
	case State_Dead:
		m_timer += Timer::GetFrameDeltaTime();
		move = { 0.0f, -m_moveSpeed * (m_timer + 1.0f), 0.0f };
		if (m_timer > 5.0f) {
			m_isRespawn = true;
			m_timer = 0.0f;
		}
		break;
	//プレイヤーにヒットした状態
	case State_Hit:
		m_timer += Timer::GetFrameDeltaTime();
		move = { 0.0f,0.0f,0.0f };
		if (m_timer > 5.0f) {
			m_isDead = true;
			m_timer = 0.0f;
		}
		break;
	}

	return move;
}

void Killer::CollisionDetection(float length, const D3DXVECTOR3& toPlayer)
{
	//プレイヤーとの距離が近ければ自身かプレイヤーの死亡フラグを立てる
	if (length <= 1.5f) {
		D3DXVECTOR3 toPlayerX = { toPlayer.x,0.0f,0.0f };
		float lengthX = D3DXVec3Length(&toPlayerX);

		D3DXVECTOR3 toPlayerY = { 0.0f,toPlayer.y,0.0f };
		float lengthY = D3DXVec3Length(&toPlayerY);

		D3DXVECTOR3 toPlayerZ = { 0.0f,0.0f,toPlayer.z };
		float lengthZ = D3DXVec3Length(&toPlayerZ);

		//Y方向に当たった
		if (toPlayerY.y > 0.0f && lengthY <= 1.3f) {
			//キラーが死亡
			player->SetTreadOnEnemy(true);
			m_state = State_Dead;

			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/Humituke.wav");
			SE->Play(false);
		}
		//X方向に当たった
		else if (lengthY <= 0.5f && lengthX <= 1.5f) {
			//プレイヤーが死亡
			m_hitPlayer = true;
			player->SetHitEnemy(m_hitPlayer);
			m_state = State_Hit;
		}
		//Z方向に当たった
		else if (lengthY <= 0.5f && lengthZ <= 0.5f) {
			//プレイヤーが死亡
			m_hitPlayer = true;
			player->SetHitEnemy(m_hitPlayer);
			m_state = State_Hit;
		}
	}

}

void Killer::RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (gameCamera != nullptr) {
		m_model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		m_model.Draw(viewMatrix, projMatrix);
		m_model.SetDrawShadowMap(false, false);
	}
}
