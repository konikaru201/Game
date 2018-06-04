#include "stdafx.h"
#include "Player.h"
#include "Scene/SceneManager.h"
#include "myEngine/HID/Pad.h"
#include "myEngine/Graphics/ShadowMap.h"
#include "myEngine/Timer/Timer.h"
#include "Map/Map.h"

Player* player;

Player::Player() :
	m_playerStateMachine(this)
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

	animation.PlayAnimation(IPlayerState::AnimationStand, 0.3f);
	animation.SetAnimationEndTime(IPlayerState::AnimationRun, 0.8f);
	animation.SetAnimationEndTime(IPlayerState::AnimationJump, 1.1f);
	animation.SetAnimationLoopflg(IPlayerState::AnimationJump, false);
	animation.SetAnimationLoopflg(IPlayerState::AnimationPose, false);
	animation.SetAnimationLoopflg(IPlayerState::AnimationDead, false);
	
	//影を描画するフラグを立てる
	SetRenderToShadow();

	//ステートマシンをゲームオブジェクトに追加
	goMgr->AddGameObject(&m_playerStateMachine);

	return true;
}

void Player::Update()
{
	if (sceneManager->GetChangeSceneFlag()) {
		//状態クラスの死亡フラグを立てる
		m_playerStateMachine.SetIsChangeState(true);
		m_playerStateMachine.Release();

		return;
	}

	if (position.y <= -20.0f) {
		m_fallPlayer = true;
	}

	//バネに当たったときジャンプ
	if (m_treadOnSpring) {
		moveSpeed.y = 0.0f;
		moveSpeed.y += jumpSpeed * 2;
		playerController.Jump();
		animation.PlayAnimation(IPlayerState::AnimationNo::AnimationJump);
		m_treadOnSpring = false;
	}

	//敵を踏んだらジャンプ
	if (m_treadOnEnemy) {
		moveSpeed.y = 0.0f;
		moveSpeed.y += jumpSpeed;
		playerController.Jump();
		animation.PlayAnimation(IPlayerState::AnimationNo::AnimationJump);
		m_treadOnEnemy = false;
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
	else if (playerController.IsOnMoveFloor2()) {
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

	//アニメーションが変わっていたら変更
	if (m_currentAnim != m_prevAnim) {
		animation.PlayAnimation(m_currentAnim, 0.3f);
	}
	
	//前のアニメーションを更新
	m_prevAnim = m_currentAnim;

	//アニメーションの更新
	animation.Update(1.0f / 60.0f);

	//ワールド行列を更新
	model.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Player::Render()
{
	model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

void Player::RenderShadow(D3DXMATRIX * viewMatrix, D3DXMATRIX * projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (player != nullptr && gameCamera != nullptr){
		model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		model.Draw(viewMatrix, projMatrix);
		model.SetDrawShadowMap(false, false);
	}
}

void Player::SilhouetteRender(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix)
{
	if (player != nullptr && gameCamera != nullptr) {
		model.SetSilhouetteRender(true);
		model.Draw(viewMatrix, projMatrix);
		model.SetSilhouetteRender(false);
	}
}