#include "stdafx.h"
#include "Player.h"
#include "Scene/GameScene.h"
#include "myEngine/HID/Pad.h"
#include "myEngine/Graphics/ShadowMap.h"
#include "myEngine/Timer/Timer.h"
#include "Map/Map.h"

Player* player;

Player::Player()
{
}

Player::~Player()
{
	//剛体を削除
	playerController.RemoveRigidBoby();
	//テクスチャの開放
	if (specularMap != NULL) {
		specularMap->Release();
	}
	if (normalMap != NULL) {
		normalMap->Release();
	}
}

bool Player::Start()
{
	//スペキュラマップをロード
	HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/utc_spec.tga",
		&specularMap
	);
	//D3DXCreateTextureFromFileAの戻り値をチェック
	if (FAILED(hr)) {
		MessageBox(NULL, "テクスチャのロードに失敗しました。スペキュラマップ", "エラー", MB_OK);
	}
	if (specularMap != NULL) {
		model.SetSpecularMap(specularMap);
	}

	//法線マップをロード
	hr = D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/utc_normal.tga",
		&normalMap
	);
	//D3DXCreateTextureFromFileAの戻り値をチェック
	if (FAILED(hr)) {
		MessageBox(NULL, "テクスチャのロードに失敗しました。法線マップ", "エラー", MB_OK);
	}
	if (normalMap != NULL) {
		model.SetNormalMap(normalMap);
	}

	//モデルデータをロードして初期化
	modelData.LoadModelData("Assets/modelData/Unity.x", &animation);
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

	//座標と向きを初期化
	position = { 0.0f,0.0f,15.0f };
	rotation = { 0.0f,0.0f,0.0f,1.0f };
	D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(180.0f));

	state = State_Walk;

	//親のワールド行列から逆行列を生成
	D3DXMATRIX parentWorldMatrixInv;
	D3DXMatrixInverse(&parentWorldMatrixInv, 0, &parentWorldMatrix);
	D3DXVec3TransformCoord(&childPosition, &position, &parentWorldMatrixInv);
	
	D3DXMATRIX secondParentWorldMatrixInv;
	D3DXMatrixInverse(&secondParentWorldMatrixInv, 0, &secondParentWorldMatrix);
	D3DXVec3TransformCoord(&secondChildPosition, &position, &secondParentWorldMatrixInv);

	//キャラクターコントローラーを初期化
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(0.3f, 1.0f);
	playerController.Init(coll, position);
	playerController.SetGravity(-20.0f);	//重力強め

	animation.PlayAnimation(AnimationStand, 0.3f);
	animation.SetAnimationEndTime(AnimationRun, 0.8f);
	animation.SetAnimationEndTime(AnimationJump, 1.1f);
	animation.SetAnimationLoopflg(AnimationJump, false);
	animation.SetAnimationLoopflg(AnimationPose, false);
	animation.SetAnimationLoopflg(AnimationDead, false);
	
	//影を描画するフラグを立てる
	SetRenderToShadow();

	return true;
}

void Player::Update()
{
	D3DXQUATERNION rot;
	D3DXQuaternionIdentity(&rot);

	switch (state)
	{
		//移動中
	case State_Walk:
		if (!gameCamera->GetCameraReset()) 
		{
			moveSpeed = Move();

			if (getStar == false && (pad->GetLStickXF() != 0.0f || pad->GetLStickYF() != 0.0f))
			{
				m_rotationFrameCount++;
				//移動しているなら向きを変える
				D3DXVECTOR3 playerDir = GetPlayerDir();
				D3DXVec3Normalize(&playerDir, &playerDir);
				D3DXVECTOR3 stickDir = dir;
				D3DXVec3Normalize(&stickDir, &stickDir);
				angle = D3DXVec3Dot(&playerDir, &stickDir);
				if (angle < -1.0f)
				{
					angle = -1.0f;
				}
				if (angle > 1.0f)
				{
					angle = 1.0f;
				}
				angle = acosf(angle);
				D3DXVECTOR3 hoge;
				D3DXVec3Cross(&hoge, &playerDir, &stickDir);
				//ベクトルが下向きか判定
				if (hoge.y < 0.0f) {
					angle *= -1.0f;
				}

				angle /= 5;
				if (m_rotationFrameCount <= 5) {
					D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);
					D3DXQuaternionMultiply(&rotation, &rotation, &rot);
					m_rotationFrameCount = 0;
				}

				if (!(playerController.IsJump())) {
					currentAnim = AnimationRun;

					timer += Timer::GetFrameDeltaTime();

					if (timer >= 0.4f) {
						CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
						SE->Init("Assets/sound/FootStep.wav");
						SE->Play(false);
						timer = 0.0f;
					}
				}
			}
			else {
				if (!(playerController.IsJump())) {
					currentAnim = AnimationStand;
				}
			}
		}

		//スプリングに当たったときジャンプ
		if (m_treadOnSpring) {
			moveSpeed.y = 0.0f;
			moveSpeed.y += jumpSpeed * 2;
			playerController.Jump();
			animation.PlayAnimation(AnimationJump);
			currentAnim = AnimationJump;
			m_treadOnSpring = false;
		}

		//敵を踏んだらジャンプ
		if (m_treadOnEnemy) {
			moveSpeed.y = 0.0f;
			moveSpeed.y += jumpSpeed;
			playerController.Jump();
			animation.PlayAnimation(AnimationJump);
			currentAnim = AnimationJump;
			m_treadOnEnemy = false;
		}

		//落ちたら又は敵に当たったら死亡
		if (position.y < -20.0f || m_hitEnemy) {
			if (m_hitEnemy) {
				currentAnim = AnimationDead;
				moveSpeed.y = -9.8f;
			}
			state = State_Dead;

			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/U_Voice_2.wav");
			SE->Play(false);
		}

		//スター獲得したらクリア
		if (getStar){
			moveSpeed.x = 0.0f;
			moveSpeed.z = 0.0f;
			if (GetIsOnGround()) {
				state = State_GetStar;

				CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
				SE->Init("Assets/sound/U_Voice_3.wav");
				SE->Play(false);
			}
		}
		
		//慣性
		if (m_moveFloorInertia) {
			m_ineltiaTime += Timer::GetFrameDeltaTime();
			//空気抵抗で少し慣性の速度を減らす
			m_airResistance = m_moveFloorSpeed * 60.0f;
			D3DXVec3Normalize(&m_airResistance, &m_airResistance);
			m_airResistance *= m_ineltiaTime;
			m_moveFloorSpeed *= 60.0f;
			moveSpeed += m_moveFloorSpeed - m_airResistance;
		}
		else if (m_moveFloor2Inertia) {
			m_ineltiaTime += Timer::GetFrameDeltaTime();
			//空気抵抗で少し慣性の速度を減らす
			m_airResistance = m_moveFloor2Speed * 60.0f;
			D3DXVec3Normalize(&m_airResistance, &m_airResistance);
			m_airResistance *= m_ineltiaTime;
			m_moveFloor2Speed *= 60.0f;
			moveSpeed += m_moveFloor2Speed - m_airResistance;
		}
		if (GetIsOnGround())
		{
			m_moveFloorInertia = false;
			m_moveFloor2Inertia = false;
			m_ineltiaTime = 0.0f;
		}

		//一番近くの移動床のワールド行列を取得
		if (map != nullptr && map->GetIsMoveFloor()) {
			if (!map->GetMoveFloorList().empty()) {
				moveFloorWorldMatrix = map->MoveFloorWorldMatrix(position);
			}
		}
		if (map != nullptr && map->GetIsMoveFloor2()) {
			if (!map->GetMoveFloor2List().empty()) {
				moveFloor2WorldMatrix = map->MoveFloor2WorldMatrix(position);
			}
		}
		//移動床に当たったらついていく
		if (playerController.IsOnMoveFloor()) {
			if (parentFirstHit) {
				//親から見たプレイヤーの座標を更新
				D3DXMATRIX moveFloorWorldMatrixInv;
				D3DXMatrixInverse(&moveFloorWorldMatrixInv, NULL, &moveFloorWorldMatrix);
				D3DXVec3TransformCoord(&moveFloorChildPosition, &position, &moveFloorWorldMatrixInv);
				parentFirstHit = false;
			}
			//プレイヤーのワールド座標に変換する
			D3DXVec3TransformCoord(&position, &moveFloorChildPosition, &moveFloorWorldMatrix);
			playerController.SetPosition(position);

			if (playerController.IsJump()) {
				m_moveFloorInertia = true;
			}

			playerController.SetMoveSpeed(moveSpeed);
			//キャラクターコントローラーを実行
			playerController.Execute();
			//座標を設定
			position = playerController.GetPosition();
			//親から見たプレイヤーの座標を更新
			D3DXMATRIX moveFloorWorldMatrixInv;
			D3DXMatrixInverse(&moveFloorWorldMatrixInv, NULL, &moveFloorWorldMatrix);
			D3DXVec3TransformCoord(&moveFloorChildPosition, &position, &moveFloorWorldMatrixInv);
		}
		else if(playerController.IsOnMoveFloor2()) {
			if (secondParentFirstHit) {
				//親から見たプレイヤーの座標を更新
				D3DXMATRIX moveFloor2WorldMatrixInv;
				D3DXMatrixInverse(&moveFloor2WorldMatrixInv, NULL, &moveFloor2WorldMatrix);
				D3DXVec3TransformCoord(&moveFloor2ChildPosition, &position, &moveFloor2WorldMatrixInv);
				secondParentFirstHit = false;
			}
			//プレイヤーのワールド座標に変換する
			D3DXVec3TransformCoord(&position, &moveFloor2ChildPosition, &moveFloor2WorldMatrix);
			playerController.SetPosition(position);

			if (playerController.IsJump()) {
				m_moveFloor2Inertia = true;
			}

			playerController.SetMoveSpeed(moveSpeed);
			//キャラクターコントローラーを実行
			playerController.Execute();
			//座標を設定
			position = playerController.GetPosition();
			//親から見たプレイヤーの座標を更新
			D3DXMATRIX moveFloor2WorldMatrixInv;
			D3DXMatrixInverse(&moveFloor2WorldMatrixInv, NULL, &moveFloor2WorldMatrix);
			D3DXVec3TransformCoord(&moveFloor2ChildPosition, &position, &moveFloor2WorldMatrixInv);
		}
		//ブロックに当たった時
		else if (playerController.IsOnBlock() == true)
		{
			if (parentFirstHit) {
				//親のワールド行列から逆行列を生成
				D3DXMATRIX parentWorldMatrixInv;
				D3DXMatrixInverse(&parentWorldMatrixInv, NULL, &parentWorldMatrix);
				D3DXVec3TransformCoord(&childPosition, &position, &parentWorldMatrixInv);
				parentFirstHit = false;
			}

			//プレイヤーのワールド座標に変換する
			D3DXVec3TransformCoord(&position, &childPosition, &parentWorldMatrix);
			playerController.SetPosition(position);

			//プレイヤーの移動速度を設定
			playerController.SetMoveSpeed(moveSpeed);
			//キャラクターコントローラーを実行
			playerController.Execute();
			//座標を設定
			position = playerController.GetPosition();

			//親から見たプレイヤーの座標を更新
			D3DXMATRIX worldMatrixInv;
			D3DXMatrixInverse(&worldMatrixInv, NULL, &parentWorldMatrix);
			D3DXVec3TransformCoord(&childPosition, &position, &worldMatrixInv);
		}
		//ブロック2に当たった時
		else if (playerController.IsOnBlock2() == true)
		{
			if (secondParentFirstHit) {
				//親のワールド行列から逆行列を生成
				D3DXMATRIX secondParentWorldMatrixInv;
				D3DXMatrixInverse(&secondParentWorldMatrixInv, NULL, &secondParentWorldMatrix);
				D3DXVec3TransformCoord(&secondChildPosition, &position, &secondParentWorldMatrixInv);
				secondParentFirstHit = false;
			}

			//プレイヤーのワールド座標に変換する
			D3DXVec3TransformCoord(&position, &secondChildPosition, &secondParentWorldMatrix);
			playerController.SetPosition(position);
			//プレイヤーの移動速度を設定
			playerController.SetMoveSpeed(moveSpeed);
			//キャラクターコントローラーを実行
			playerController.Execute();
			//座標を設定
			position = playerController.GetPosition();

			//親から見たプレイヤーの座標を更新
			D3DXMATRIX worldMatrixInv;
			D3DXMatrixInverse(&worldMatrixInv, NULL, &secondParentWorldMatrix);
			D3DXVec3TransformCoord(&secondChildPosition, &position, &worldMatrixInv);
		}
		else {
			//プレイヤーの移動速度を設定
			playerController.SetMoveSpeed(moveSpeed);
			//キャラクターコントローラーを実行
			playerController.Execute();
			//座標を設定
			position = playerController.GetPosition();
			parentFirstHit = true;
			secondParentFirstHit = true;
		}

		break;

		//死亡時
	case State_Dead:
		//g_shadowMap.SetPlayerDead(true);
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
		//プレイヤーの移動速度を設定
		playerController.SetMoveSpeed(moveSpeed);
		//キャラクターコントローラーを実行
		playerController.Execute();
		//座標を設定
		position = playerController.GetPosition();

		timer += Timer::GetFrameDeltaTime();
		if (timer >= 2.0f) {
			m_playerDead = true;
		}
		break;

		//スター獲得時
	case State_GetStar:
		currentAnim = AnimationPose;
		if (!animation.IsPlay()) {
			animationEnd = true;
		}
		break;
	}
	
	//アニメーションが変わっていたら変更
	if (currentAnim != prevAnim) {
		animation.PlayAnimation(currentAnim, 0.3f);
	}
	

	//前のアニメーションを保存
	prevAnim = currentAnim;

	//アニメーションの更新
	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Player::Render()
{
	model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetViewProjectionMatrix());
}

void Player::RenderShadow(D3DXMATRIX * viewMatrix, D3DXMATRIX * projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (player != nullptr && gameCamera != nullptr){
		model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		model.Draw(viewMatrix, projMatrix);
		model.SetDrawShadowMap(false, false);
	}
}

void Player::DepthStencilRender(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix)
{
	if (player != nullptr && gameCamera != nullptr) {
		model.SetDepthStencilRender(true);
		model.Draw(viewMatrix, projMatrix);
		model.SetDepthStencilRender(false);
	}
}

D3DXVECTOR3 Player::Move()
{
	//移動速度を取得
	D3DXVECTOR3 move = playerController.GetMoveSpeed();

	//スティックの入力量を取得
	D3DXVECTOR3 moveDir;
	moveDir.y = 0.0f;
	moveDir.x = pad->GetLStickXF();
	moveDir.z = pad->GetLStickYF();

	//カメラの逆行列を作成
	D3DXMATRIX ViewMatrix = gameCamera->GetViewMatrix();
	D3DXMATRIX ViewMatrixInv;
	D3DXMatrixInverse(&ViewMatrixInv, 0, &ViewMatrix);

	//カメラ空間から見た奥方向のベクトル
	D3DXVECTOR3 cameraVecZ;
	cameraVecZ.x = ViewMatrixInv.m[2][0];
	cameraVecZ.y = 0.0f;
	cameraVecZ.z = ViewMatrixInv.m[2][2];
	D3DXVec3Normalize(&cameraVecZ, &cameraVecZ);

	//カメラ空間から見た横方向のベクトル
	D3DXVECTOR3 cameraVecX;
	cameraVecX.x = ViewMatrixInv.m[0][0];
	cameraVecX.y = 0.0f;
	cameraVecX.z = ViewMatrixInv.m[0][2];
	D3DXVec3Normalize(&cameraVecX, &cameraVecX);

	//キャラクターの向きを計算
	dir.x = cameraVecX.x * moveDir.x + cameraVecZ.x * moveDir.z;
	dir.y = 0.0f;
	dir.z = cameraVecX.z * moveDir.x + cameraVecZ.z * moveDir.z;

	//移動してるなら徐々に加速
	if (moveDir.x != 0.0f || moveDir.z != 0.0f) {
		acceleration += 0.1f;
	}
	else {
		acceleration -= 0.5f;
		if (acceleration < 0.0f) {
			acceleration = 0.0f;
		}
	}

	//限界速度を超えたら移動速度を限界速度に設定
	if (acceleration > speedLimit) {
		acceleration = speedLimit;
	}

	//向きが90度以上変わったら速度を下げる
	if (currentDir.x != 0.0f || currentDir.y != 0.0f || currentDir.z != 0.0f){
		if (D3DXVec3Dot(&currentDir, &dir) < -0.1f) {
			acceleration = 1.0f;
		}
	}
	//1フレーム前の向きを保存
	currentDir = dir;

	//移動速度を計算
	move.x = dir.x * acceleration;
	move.z = dir.z * acceleration;

	//Aボタンが押されたらジャンプ
	if (pad->IsTrigger(pad->enButtonA)
		&& !playerController.IsJump()
		&& GetIsOnGround())
	{
		move.y = 10.0f;

		playerController.Jump();

		animation.PlayAnimation(AnimationJump);
		currentAnim = AnimationJump;
		CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
		SE->Init("Assets/sound/U_Voice_1.wav");
		SE->Play(false);
	}
	return move;
}