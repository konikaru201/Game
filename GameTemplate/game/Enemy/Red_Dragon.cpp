#include "stdafx.h"
#include "Red_Dragon.h"
#include "Scene/SceneManager.h"
#include "myEngine/Timer/Timer.h"
#include "myEngine/Sound/SoundSource.h"

Red_Dragon::Red_Dragon()
{
}

Red_Dragon::~Red_Dragon()
{
}

void Red_Dragon::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	//モデルの初期化
	m_modelData.LoadModelData("Assets/modelData/Red_Dragon.x", &m_animation);
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

	m_model.UpdateWorldMatrix(pos, rot, { 1.0f,1.0f,1.0f });

	m_matrix = m_modelData.FindBoneWorldMatrix("B_bip01");

	m_position = pos;
	m_rotation = rot;
	m_initPosition = pos;

	m_state = State_Wait;
	m_currentAnim = AnimationWait;

	m_animation.SetAnimationLoopflg(AnimationDead, false);
	m_animation.PlayAnimation(AnimationWait, 0.3f);

	//剛体の作成
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(0.5f, 1.5f);

	//剛体の情報を設定
	RigidBodyInfo rbinfo;
	rbinfo.collider = coll;
	rbinfo.mass = 0.0f;
	rbinfo.pos = m_position;
	rbinfo.rot = m_rotation;
	//剛体を作成
	m_rigidBody.Create(rbinfo);

	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));

	//作成した剛体を物理ワールドに追加
	g_physicsWorld->AddRigidBody(&m_rigidBody);

	//影を描画するフラグを立てる
	SetRenderToShadow();

	//パーティクルの初期化
	SParticleEmitParameter param;
	param.texturePath = "Assets/sprite/FireParticleGlow.png";
	param.w = 0.5f;
	param.h = 0.5f;
	param.intervalTime = 0.05f;
	param.initSpeed = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	param.position = m_position;
	param.alpha = 1.0f;
	m_particleEmitter.Init(param);
}

void Red_Dragon::Update()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		//剛体を削除
		g_physicsWorld->RemoveRigidBody(&m_rigidBody);
		return;
	}

	D3DXVECTOR3 moveSpeed = Move();
	m_position += moveSpeed / 60.0f;

	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));

	//アニメーションが変わっていたら変更
	if (m_currentAnim != m_prevAnim) {
		m_animation.PlayAnimation(m_currentAnim, 0.3f);
	}

	//前のアニメーションを保存
	m_prevAnim = m_currentAnim;

	m_animation.Update(1.0f / 60.0f);
	m_model.UpdateWorldMatrix(m_position, m_rotation, D3DXVECTOR3( 1.0f,1.0f,1.0f ));
}

void Red_Dragon::Render()
{
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

D3DXVECTOR3 Red_Dragon::Move()
{
	//移動速度を取得
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };

	//モデルのZ方向を取得
	D3DXVECTOR3 direction;
	D3DXMATRIX mWorld = m_model.GetWorldMatrix();
	direction.x = mWorld.m[2][0];
	direction.y = mWorld.m[2][1];
	direction.z = mWorld.m[2][2];
	//モデルの中心座標を取得
	D3DXVECTOR3 modelPosition;
	modelPosition.x = m_matrix->m[3][0];
	modelPosition.y = m_matrix->m[3][1];
	modelPosition.z = m_matrix->m[3][2];

	//プレイヤーの位置を取得
	D3DXVECTOR3 playerPos = player->GetPosition();
	playerPos.y += 0.5f;
	//プレイヤーへのベクトルを計算
	D3DXVECTOR3 toPlayer = playerPos - modelPosition;
	
	//初期化
	float length = D3DXVec3Length(&toPlayer);
	float angle = 0.0f;
	D3DXVECTOR3 AxisZ = { 0.0f,0.0f,1.0f };
	D3DXVECTOR3 toInitPosition = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 Cross = { 0.0f,0.0f,0.0f };
	D3DXQUATERNION rot;
	D3DXQuaternionIdentity(&rot);

	if (m_state != State_Dead && m_state != State_Hit) {
		//プレイヤーとの当たり判定を調べる
		CollisionDetection(length, toPlayer);
	}

	toPlayer.y = 0.0f;

	switch (m_state)
	{
		//待機中
	case State_Wait:
		//プレイヤーとの距離と視野角で発見されたか判定
		length = D3DXVec3Length(&toPlayer);
		D3DXVec3Normalize(&toPlayer, &toPlayer);
		angle = D3DXVec3Dot(&toPlayer, &direction);
		angle = acos(angle);
		//発見された
		if (fabsf(angle) < D3DXToRadian(30.0f) && length < 12.0f) {
			m_state = State_Find;
			m_timer = 0.0f;
			break;
		}

		m_timer += Timer::GetFrameDeltaTime();
		if (m_timer > 5.0f){
			m_state = State_Move;
			m_timer = 0.0f;
			break;
		}
		m_currentAnim = AnimationWait;
		break;

		//移動中
	case State_Move:
		//プレイヤーとの距離と視野角で発見されたか判定
		length = D3DXVec3Length(&toPlayer);
		D3DXVec3Normalize(&toPlayer, &toPlayer);
		angle = D3DXVec3Dot(&toPlayer, &direction);
		angle = acos(angle);
		//発見された
		if (fabsf(angle) < D3DXToRadian(30.0f) && length < 12.0f) {
			m_state = State_Find;
			break;
		}

		move = m_moveSpeed * m_XDir;

		//移動方向に向きを変える
		angle = D3DXVec3Dot(&direction, &m_XDir);
		angle = acosf(angle);
		D3DXVec3Cross(&Cross, &direction, &m_XDir);
		//ベクトルが下向きか判定
		if (Cross.y < 0.0f) {
			angle *= -1.0f;
		}
		D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);
		D3DXQuaternionMultiply(&m_rotation, &m_rotation, &rot);

		//現在の座標から初期座標の距離を計算
		toInitPosition = m_position - m_initPosition;
		toInitPosition += move / 60.0f;
		length = D3DXVec3Length(&toInitPosition);
		//移動範囲を超えたら待機
		if (length > 8.0f) {
			m_state = State_Wait;
			m_XDir *= -1.0f;
			break;
		}

		m_currentAnim = AnimationRun;
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
		toPlayer *= m_moveSpeed;
		move = toPlayer;
		move.y = 0.0f;

		//プレイヤーとの距離が近ければ攻撃に移行
		if (length < 2.0f) {
			m_state = State_Attack;
			break;
		}

		//現在の座標から初期座標の距離を計算
		toInitPosition = m_position - m_initPosition;
		toInitPosition += move / 60.0f;
		length = D3DXVec3Length(&toInitPosition);

		//初期位置から離れると追いかけない
		if (length > 10.0f) {
			m_state = State_Miss;
			break;
		}

		D3DXQuaternionRotationAxis(&m_rotation, &m_up, angle);

		m_currentAnim = AnimationRun;
		break;

		//見失った状態
	case State_Miss:
		m_changeDir = true;
		m_currentAnim = AnimationWait;
		m_timer += Timer::GetFrameDeltaTime();
		//プレイヤーとの距離と視野角で発見されたか判定
		length = D3DXVec3Length(&toPlayer);
		D3DXVec3Normalize(&toPlayer, &toPlayer);
		angle = D3DXVec3Dot(&toPlayer, &direction);
		angle = acos(angle);
		//発見された
		if (fabsf(angle) < D3DXToRadian(30.0f) && length < 12.0f) {
			m_state = State_Find;
			m_timer = 0.0f;
			break;
		}

		//一定時間経つと初期座標に戻る
		if (m_timer > 3.0f) {
			//現在の座標から初期座標への距離と方向を計算
			toInitPosition = m_initPosition - m_position;
			length = D3DXVec3Length(&toInitPosition);
			D3DXVec3Normalize(&toInitPosition, &toInitPosition);

			if (m_changeDir) {
				//移動方向に向きを変える
				angle = D3DXVec3Dot(&direction, &toInitPosition);
				if (angle < -1.0f)
				{
					angle = -1.0f;
				}
				if (angle > 1.0f)
				{
					angle = 1.0f;
				}
				angle = acosf(angle);
				D3DXVec3Cross(&Cross, &direction, &toInitPosition);
				//ベクトルが下向きか判定
				if (Cross.y < 0.0f) {
					angle *= -1.0f;
				}
				D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);
				D3DXQuaternionMultiply(&m_rotation, &m_rotation, &rot);

				m_changeDir = false;
			}

			//移動速度を計算
			toInitPosition *= m_moveSpeed;
			move = toInitPosition;
			move.y = 0.0f;

			//初期座標に戻ったら待機状態
			if (length < 0.2f) {
				m_state = State_Wait;
				m_timer = 0.0f;
				break;
			}
			m_currentAnim = AnimationRun;
		}
		break;

		//攻撃中
	case State_Attack:
		m_particleEmitter.SetSpeed(GetDirection() * 1.5f);
		m_particleEmitter.SetPosition(modelPosition);
		m_particleEmitter.Update();
		m_timer += Timer::GetFrameDeltaTime();

		m_attackTimer += Timer::GetFrameDeltaTime();
		if (m_attackTimer >= 0.5f) {
			length = D3DXVec3Length(&toPlayer);
			D3DXVec3Normalize(&toPlayer, &toPlayer);
			angle = D3DXVec3Dot(&toPlayer, &direction);
			angle = acos(angle);
			//攻撃が当たった
			if (fabsf(angle) < D3DXToRadian(15.0f) && length < 5.0f) {
				if (m_attackTimer >= 0.8f) {
					//プレイヤーが死亡
					m_hitPlayer = true;
					player->SetHitEnemy(m_hitPlayer);
					m_state = State_Hit;
				}
			}
			else {
				m_attackTimer = 0.0f;
			}
		}

		if (m_timer > 2.5f) {
			length = D3DXVec3Length(&toPlayer);
			D3DXVec3Normalize(&toPlayer, &toPlayer);
			angle = D3DXVec3Dot(&toPlayer, &direction);
			angle = acos(angle);
			//発見された
			if (fabsf(angle) < D3DXToRadian(30.0f) && length < 12.0f) {
				m_findAgainFlag = true;
			}

			if (m_findAgainFlag) {
				m_state = State_Find;
				m_findAgainFlag = false;
			}
			else if (!m_findAgainFlag && length > 2.0f) {
				m_state = State_Miss;
			}
			m_timer = 0.0f;
		}

		m_currentAnim = AnimationAttack;

		m_soundTimer += Timer::GetFrameDeltaTime();
		if (m_soundTimer >= 1.0f) {
			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/Fire.wav");
			SE->Play(false);
			m_soundTimer = 0.0f;
			SE->SetisDead();
		}

		break;
		//死亡時
	case State_Dead:
		move = { 0.0f,0.0f,0.0f };
		m_currentAnim = AnimationDead;
		if (!m_animation.IsPlay()) {
			SetisDead();
			//剛体を削除
			g_physicsWorld->RemoveRigidBody(&m_rigidBody);
		}

		break;
		//プレイヤーにヒット
	case State_Hit:
		m_timer += Timer::GetFrameDeltaTime();
		move = { 0.0f,0.0f,0.0f };
		if (m_timer >= 5.0f) {
			m_isDead = true;
			m_timer = 0.0f;
		}
		break;
	}

	return move;
}

void Red_Dragon::CollisionDetection(float length, const D3DXVECTOR3& toPlayer)
{
	if (length <= 1.5f) {
		D3DXVECTOR3 toPlayerXZ = { toPlayer.x,0.0f,toPlayer.z };
		float lengthXZ = D3DXVec3Length(&toPlayerXZ);

		D3DXVECTOR3 toPlayerY = { 0.0f,toPlayer.y,0.0f };
		float lengthY = D3DXVec3Length(&toPlayerY);

		//Y方向に当たった
		if (toPlayerY.y > 0.0f && lengthY <= 0.95f && lengthXZ <= 0.7f) {
			//ドラゴンが死亡
			player->SetTreadOnEnemy(true);
			m_state = State_Dead;

			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/Humituke.wav");
			SE->Play(false);
		}
		//XZ方向に当たった
		else if (lengthY <= 0.3f && lengthXZ <= 0.9f) {
			//プレイヤーが死亡
			m_hitPlayer = true;
			player->SetHitEnemy(m_hitPlayer);
			m_state = State_Hit;
		}
	}
}

void Red_Dragon::RenderShadow(D3DXMATRIX * viewMatrix, D3DXMATRIX * projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (gameCamera != nullptr) {
		m_model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		m_model.Draw(viewMatrix, projMatrix);
		m_model.SetDrawShadowMap(false, false);
	}
}
