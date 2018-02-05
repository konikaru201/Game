#include "stdafx.h"
#include "Red_Dragon.h"
#include "Scene/GameScene.h"
#include "myEngine/Timer/Timer.h"

Red_Dragon::Red_Dragon()
{
}

Red_Dragon::~Red_Dragon()
{
}

void Red_Dragon::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	//モデルの初期化
	modelData.LoadModelData("Assets/modelData/Red_Dragon.x", &animation);
	model.Init(&modelData);
	model.SetLight(&gameScene->GetLight());
	model.UpdateWorldMatrix(pos, rot, { 1.0f,1.0f,1.0f });

	matrix = modelData.FindBoneWorldMatrix("B_bip01");

	position = pos;
	rotation = rot;
	initPosition = pos;

	state = State_Wait;
	currentAnim = AnimationWait;

	animation.PlayAnimation(AnimationWait, 0.3f);

	//剛体の作成
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(0.5f, 1.5f);

	//剛体の情報を設定
	RigidBodyInfo rbinfo;
	rbinfo.collider = coll;
	rbinfo.mass = 0.0f;
	rbinfo.pos = position;
	rbinfo.rot = rotation;
	//剛体を作成
	rigidBody.Create(rbinfo);

	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(position.x, position.y, position.z));

	//作成した剛体を物理ワールドに追加
	g_physicsWorld->AddRigidBody(&rigidBody);

	//パーティクルの初期化
	SParticleEmitParameter param;
	param.texturePath = "Assets/sprite/FireParticleGlow.png";
	param.w = 0.5f;
	param.h = 0.5f;
	param.intervalTime = 0.2f;
	param.initSpeed = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	param.position = position;
	param.alpha = 1.0f;
	particleEmitter.Init(param);
}

void Red_Dragon::Update()
{
	if (gameScene == nullptr || gameScene->GetChengeStage() || isDead) {
		SetisDead();
		//剛体を削除
		g_physicsWorld->RemoveRigidBody(&rigidBody);
		return;
	}

	D3DXVECTOR3 moveSpeed = Move();
	position += moveSpeed / 60.0f;

	btTransform& trans = rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(position.x, position.y, position.z));

	//アニメーションが変わっていたら変更
	if (currentAnim != prevAnim) {
		animation.PlayAnimation(currentAnim, 0.3f);
	}

	//前のアニメーションを保存
	prevAnim = currentAnim;

	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(position, rotation, D3DXVECTOR3( 1.0f,1.0f,1.0f ));
}

void Red_Dragon::Render()
{
	if (gameScene == nullptr) { return; }
	model.Draw(&gameScene->GetGameCamera()->GetViewMatrix(), &gameScene->GetGameCamera()->GetViewProjectionMatrix());
}

D3DXVECTOR3 Red_Dragon::Move()
{
	//移動速度を取得
	D3DXVECTOR3 move = { 0.0f,0.0f,0.0f };

	//モデルのZ方向を取得
	D3DXVECTOR3 direction;
	D3DXMATRIX mWorld = model.GetWorldMatrix();
	direction.x = mWorld.m[2][0];
	direction.y = mWorld.m[2][1];
	direction.z = mWorld.m[2][2];
	//モデルの中心座標を取得
	D3DXVECTOR3 modelPosition;
	modelPosition.x = matrix->m[3][0];
	modelPosition.y = matrix->m[3][1];
	modelPosition.z = matrix->m[3][2];

	//プレイヤーの位置を取得
	D3DXVECTOR3 playerPos = g_player->GetPosition();
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

	//プレイヤーとの当たり判定を調べる
	CollisionDetection(length, toPlayer);
	toPlayer.y = 0.0f;

	switch (state)
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
			state = State_Find;
			timer = 0.0f;
			break;
		}

		timer += Timer::GetFrameDeltaTime();
		if (timer > 5.0f){
			state = State_Move;
			timer = 0.0f;
			break;
		}
		currentAnim = AnimationWait;
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
			state = State_Find;
			break;
		}

		move = moveSpeed * XDir;

		//移動方向に向きを変える
		angle = D3DXVec3Dot(&direction, &XDir);
		angle = acosf(angle);
		D3DXVec3Cross(&Cross, &direction, &XDir);
		//ベクトルが下向きか判定
		if (Cross.y < 0.0f) {
			angle *= -1.0f;
		}
		D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);
		D3DXQuaternionMultiply(&rotation, &rotation, &rot);

		//現在の座標から初期座標の距離を計算
		toInitPosition = position - initPosition;
		toInitPosition += move / 60.0f;
		length = D3DXVec3Length(&toInitPosition);
		//移動範囲を超えたら待機
		if (length > 8.0f) {
			state = State_Wait;
			XDir *= -1.0f;
			break;
		}

		currentAnim = AnimationRun;
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
		toPlayer *= moveSpeed;
		move = toPlayer;
		move.y = 0.0f;

		//プレイヤーとの距離が離れると見失う
		if (length > 20.0f) {
			state = State_Miss;
			break;
		}
		//プレイヤーとの距離が近ければ攻撃に移行
		else if(length < 2.0f){
			state = State_Attack;
			break;
		}

		D3DXQuaternionRotationAxis(&rotation, &up, angle);

		currentAnim = AnimationRun;
		break;

		//見失った状態
	case State_Miss:
		changeDir = true;
		currentAnim = AnimationWait;
		timer += Timer::GetFrameDeltaTime();
		//プレイヤーとの距離と視野角で発見されたか判定
		length = D3DXVec3Length(&toPlayer);
		D3DXVec3Normalize(&toPlayer, &toPlayer);
		angle = D3DXVec3Dot(&toPlayer, &direction);
		angle = acos(angle);
		//発見された
		if (fabsf(angle) < D3DXToRadian(30.0f) && length < 12.0f) {
			state = State_Find;
			timer = 0.0f;
			break;
		}

		//一定時間経つと初期座標に戻る
		if (timer > 3.0f) {
			//現在の座標から初期座標への距離と方向を計算
			toInitPosition = initPosition - position;
			length = D3DXVec3Length(&toInitPosition);
			D3DXVec3Normalize(&toInitPosition, &toInitPosition);

			if (changeDir) {
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
				D3DXQuaternionMultiply(&rotation, &rotation, &rot);

				changeDir = false;
			}

			//移動速度を計算
			toInitPosition *= moveSpeed;
			move = toInitPosition;
			move.y = 0.0f;

			//初期座標に戻ったら待機状態
			if (length < 0.2f) {
				state = State_Wait;
				timer = 0.0f;
				break;
			}
			currentAnim = AnimationRun;
		}
		break;

		//攻撃中
	case State_Attack:
		particleEmitter.SetSpeed(GetDirection());
		particleEmitter.SetPosition(modelPosition);
		particleEmitter.Update();
		timer += Timer::GetFrameDeltaTime();
		if (timer > 2.5f) {
			length = D3DXVec3Length(&toPlayer);
			D3DXVec3Normalize(&toPlayer, &toPlayer);
			angle = D3DXVec3Dot(&toPlayer, &direction);
			angle = acos(angle);
			//発見された
			if (fabsf(angle) < D3DXToRadian(30.0f) && length < 12.0f) {
				findAgainFlag = true;
			}

			if (findAgainFlag) {
				state = State_Find;
				findAgainFlag = false;
			}
			else if (!findAgainFlag && length > 2.0f) {
				state = State_Miss;
			}
			timer = 0.0f;
		}
		currentAnim = AnimationAttack;

		soundTimer += Timer::GetFrameDeltaTime();
		if (soundTimer >= 1.0f) {
			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/Fire.wav");
			SE->Play(false);
			soundTimer = 0.0f;
			SE->SetisDead();
		}

		break;
		//死亡時
	case State_Dead:
		move = { 0.0f,0.0f,0.0f };
		isDead = true;
		//仮アニメーション
		currentAnim = AnimationWait;
		break;
		//プレイヤーにヒット
	case State_Hit:
		timer += Timer::GetFrameDeltaTime();
		move = { 0.0f,0.0f,0.0f };
		if (timer >= 5.0f) {
			isDead = true;
			timer = 0.0f;
		}
		currentAnim = AnimationWait;
		break;
	}

	return move;
}

void Red_Dragon::CollisionDetection(float Length, const D3DXVECTOR3& ToPlayer)
{
	if (Length <= 1.5f) {
		D3DXVECTOR3 toPlayerX = { ToPlayer.x,0.0f,0.0f };
		float lengthX = D3DXVec3Length(&toPlayerX);

		D3DXVECTOR3 toPlayerY = { 0.0f,ToPlayer.y,0.0f };
		float lengthY = D3DXVec3Length(&toPlayerY);

		D3DXVECTOR3 toPlayerZ = { 0.0f,0.0f,ToPlayer.z };
		float lengthZ = D3DXVec3Length(&toPlayerZ);

		//Y方向に当たった
		if (toPlayerY.y > 0.0f && lengthY <= 0.5f) {
			//ドラゴンが死亡
			g_player->SetTreadOnEnemy(true);
			state = State_Dead;
		}
		//X方向に当たった
		else if (lengthY <= 0.5f && lengthX <= 1.5f) {
			////プレイヤーが死亡
			m_hitPlayer = true;
			g_player->SetHitEnemy(m_hitPlayer);
			state = State_Hit;
		}
		//Z方向に当たった
		else if (lengthY <= 0.5f && lengthZ <= 0.8f) {
			//プレイヤーが死亡
			m_hitPlayer = true;
			g_player->SetHitEnemy(m_hitPlayer);
			state = State_Hit;
		}
	}
}