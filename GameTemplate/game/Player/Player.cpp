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
	m_playerController.RemoveRigidBoby();
	//テクスチャの開放
	if (m_specularMap != NULL) {
		m_specularMap->Release();
	}
	if (m_normalMap != NULL) {
		m_normalMap->Release();
	}
}

bool Player::Start()
{
	//スペキュラマップをロード
	HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/utc_spec.tga",
		&m_specularMap
	);
	//D3DXCreateTextureFromFileAの戻り値をチェック
	if (FAILED(hr)) {
		MessageBox(NULL, "テクスチャのロードに失敗しました。スペキュラマップ", "エラー", MB_OK);
	}
	if (m_specularMap != NULL) {
		m_model.SetSpecularMap(m_specularMap);
	}

	//法線マップをロード
	hr = D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/utc_normal.tga",
		&m_normalMap
	);
	//D3DXCreateTextureFromFileAの戻り値をチェック
	if (FAILED(hr)) {
		MessageBox(NULL, "テクスチャのロードに失敗しました。法線マップ", "エラー", MB_OK);
	}
	if (m_normalMap != NULL) {
		m_model.SetNormalMap(m_normalMap);
	}

	//モデルデータをロードして初期化
	m_modelData.LoadModelData("Assets/modelData/Unity.x", &m_animation);
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

	//座標と向きを初期化
	m_position = { 0.0f,0.0f,15.0f };
	m_rotation = { 0.0f,0.0f,0.0f,1.0f };
	D3DXQuaternionRotationAxis(&m_rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(180.0f));

	//親のワールド行列から逆行列を生成
	D3DXMATRIX parentWorldMatrixInv;
	D3DXMatrixInverse(&parentWorldMatrixInv, 0, &m_parentWorldMatrix);
	D3DXVec3TransformCoord(&m_childPosition, &m_position, &parentWorldMatrixInv);
	
	D3DXMATRIX secondParentWorldMatrixInv;
	D3DXMatrixInverse(&secondParentWorldMatrixInv, 0, &m_secondParentWorldMatrix);
	D3DXVec3TransformCoord(&m_secondChildPosition, &m_position, &secondParentWorldMatrixInv);

	//キャラクターコントローラーを初期化
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(0.3f, 1.0f);
	m_playerController.Init(coll, m_position);
	m_playerController.SetGravity(-20.0f);	//重力強め

	m_animation.PlayAnimation(IPlayerState::AnimationStand, 0.3f);
	m_animation.SetAnimationEndTime(IPlayerState::AnimationRun, 0.8f);
	m_animation.SetAnimationEndTime(IPlayerState::AnimationJump, 1.1f);
	m_animation.SetAnimationLoopflg(IPlayerState::AnimationJump, false);
	m_animation.SetAnimationLoopflg(IPlayerState::AnimationPose, false);
	m_animation.SetAnimationLoopflg(IPlayerState::AnimationDead, false);
	
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

	if (sceneManager->GetScene() == SceneManager::stateStageSelect) {
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}

	//落下したらフラグをたてる
	if (m_position.y <= -20.0f) {
		m_fallPlayer = true;
	}

	//バネに当たったときジャンプ
	if (m_treadOnSpring) {
		m_moveSpeed.y = 0.0f;
		m_moveSpeed.y += m_jumpSpeed * 2;
		m_playerController.Jump();
		m_animation.PlayAnimation(IPlayerState::AnimationNo::AnimationJump);
		m_treadOnSpring = false;
	}

	//敵を踏んだらジャンプ
	if (m_treadOnEnemy) {
		m_moveSpeed.y = 0.0f;
		m_moveSpeed.y += m_jumpSpeed;
		m_playerController.Jump();
		m_animation.PlayAnimation(IPlayerState::AnimationNo::AnimationJump);
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
		m_moveSpeed += m_moveFloorSpeed - m_airResistance;
	}
	else if (m_moveFloor2Inertia) {
		m_ineltiaTime += Timer::GetFrameDeltaTime();
		//空気抵抗で少し慣性の速度を減らす
		m_airResistance = m_moveFloor2Speed * 60.0f;
		D3DXVec3Normalize(&m_airResistance, &m_airResistance);
		m_airResistance *= m_ineltiaTime;
		m_moveFloor2Speed *= 60.0f;
		m_moveSpeed += m_moveFloor2Speed - m_airResistance;
	}
	if (GetIsOnGround())
	{
		m_moveFloorInertia = false;
		m_moveFloor2Inertia = false;
		m_ineltiaTime = 0.0f;
	}

	//一番近くの移動床のワールド行列を取得
	if (map != nullptr && !map->GetMoveFloorList().empty()) {
		m_moveFloorWorldMatrix = map->GetMoveFloorWorldMatrix(m_position);
	}
	if (map != nullptr && !map->GetMoveFloor2List().empty()) {
		m_moveFloor2WorldMatrix = map->GetMoveFloor2WorldMatrix(m_position);
	}
	//移動床に当たったらついていく
	if (m_playerController.IsOnMoveFloor()) {
		if (m_parentFirstHit) {
			//親から見たプレイヤーの座標を更新
			D3DXMATRIX moveFloorWorldMatrixInv;
			D3DXMatrixInverse(&moveFloorWorldMatrixInv, NULL, &m_moveFloorWorldMatrix);
			D3DXVec3TransformCoord(&m_moveFloorChildPosition, &m_position, &moveFloorWorldMatrixInv);
			m_parentFirstHit = false;
		}
		//プレイヤーのワールド座標に変換する
		D3DXVec3TransformCoord(&m_position, &m_moveFloorChildPosition, &m_moveFloorWorldMatrix);
		m_playerController.SetPosition(m_position);

		if (m_playerController.IsJump()) {
			m_moveFloorInertia = true;
		}

		m_playerController.SetMoveSpeed(m_moveSpeed);
		//キャラクターコントローラーを実行
		m_playerController.Execute();
		//座標を設定
		m_position = m_playerController.GetPosition();
		//親から見たプレイヤーの座標を更新
		D3DXMATRIX moveFloorWorldMatrixInv;
		D3DXMatrixInverse(&moveFloorWorldMatrixInv, NULL, &m_moveFloorWorldMatrix);
		D3DXVec3TransformCoord(&m_moveFloorChildPosition, &m_position, &moveFloorWorldMatrixInv);
	}
	else if (m_playerController.IsOnMoveFloor2()) {
		if (m_secondParentFirstHit) {
			//親から見たプレイヤーの座標を更新
			D3DXMATRIX moveFloor2WorldMatrixInv;
			D3DXMatrixInverse(&moveFloor2WorldMatrixInv, NULL, &m_moveFloor2WorldMatrix);
			D3DXVec3TransformCoord(&m_moveFloor2ChildPosition, &m_position, &moveFloor2WorldMatrixInv);
			m_secondParentFirstHit = false;
		}
		//プレイヤーのワールド座標に変換する
		D3DXVec3TransformCoord(&m_position, &m_moveFloor2ChildPosition, &m_moveFloor2WorldMatrix);
		m_playerController.SetPosition(m_position);

		if (m_playerController.IsJump()) {
			m_moveFloor2Inertia = true;
		}

		m_playerController.SetMoveSpeed(m_moveSpeed);
		//キャラクターコントローラーを実行
		m_playerController.Execute();
		//座標を設定
		m_position = m_playerController.GetPosition();
		//親から見たプレイヤーの座標を更新
		D3DXMATRIX moveFloor2WorldMatrixInv;
		D3DXMatrixInverse(&moveFloor2WorldMatrixInv, NULL, &m_moveFloor2WorldMatrix);
		D3DXVec3TransformCoord(&m_moveFloor2ChildPosition, &m_position, &moveFloor2WorldMatrixInv);
	}
	//ブロックに当たった時
	else if (m_playerController.IsOnBlock() == true)
	{
		if (m_parentFirstHit) {
			//親のワールド行列から逆行列を生成
			D3DXMATRIX parentWorldMatrixInv;
			D3DXMatrixInverse(&parentWorldMatrixInv, NULL, &m_parentWorldMatrix);
			D3DXVec3TransformCoord(&m_childPosition, &m_position, &parentWorldMatrixInv);
			m_parentFirstHit = false;
		}

		//プレイヤーのワールド座標に変換する
		D3DXVec3TransformCoord(&m_position, &m_childPosition, &m_parentWorldMatrix);
		m_playerController.SetPosition(m_position);

		//プレイヤーの移動速度を設定
		m_playerController.SetMoveSpeed(m_moveSpeed);
		//キャラクターコントローラーを実行
		m_playerController.Execute();
		//座標を設定
		m_position = m_playerController.GetPosition();

		//親から見たプレイヤーの座標を更新
		D3DXMATRIX worldMatrixInv;
		D3DXMatrixInverse(&worldMatrixInv, NULL, &m_parentWorldMatrix);
		D3DXVec3TransformCoord(&m_childPosition, &m_position, &worldMatrixInv);
	}
	//ブロック2に当たった時
	else if (m_playerController.IsOnBlock2() == true)
	{
		if (m_secondParentFirstHit) {
			//親のワールド行列から逆行列を生成
			D3DXMATRIX secondParentWorldMatrixInv;
			D3DXMatrixInverse(&secondParentWorldMatrixInv, NULL, &m_secondParentWorldMatrix);
			D3DXVec3TransformCoord(&m_secondChildPosition, &m_position, &secondParentWorldMatrixInv);
			m_secondParentFirstHit = false;
		}

		//プレイヤーのワールド座標に変換する
		D3DXVec3TransformCoord(&m_position, &m_secondChildPosition, &m_secondParentWorldMatrix);
		m_playerController.SetPosition(m_position);
		//プレイヤーの移動速度を設定
		m_playerController.SetMoveSpeed(m_moveSpeed);
		//キャラクターコントローラーを実行
		m_playerController.Execute();
		//座標を設定
		m_position = m_playerController.GetPosition();

		//親から見たプレイヤーの座標を更新
		D3DXMATRIX worldMatrixInv;
		D3DXMatrixInverse(&worldMatrixInv, NULL, &m_secondParentWorldMatrix);
		D3DXVec3TransformCoord(&m_secondChildPosition, &m_position, &worldMatrixInv);
	}
	else {
		//プレイヤーの移動速度を設定
		m_playerController.SetMoveSpeed(m_moveSpeed);
		//キャラクターコントローラーを実行
		m_playerController.Execute();
		//座標を設定
		m_position = m_playerController.GetPosition();
		m_parentFirstHit = true;
		m_secondParentFirstHit = true;
	}

	//アニメーションが変わっていたら変更
	if (m_currentAnim != m_prevAnim) {
		m_animation.PlayAnimation(m_currentAnim, 0.3f);
	}
	
	//前のアニメーションを更新
	m_prevAnim = m_currentAnim;

	//アニメーションの更新
	m_animation.Update(1.0f / 60.0f);

	//ワールド行列を更新
	m_model.UpdateWorldMatrix(m_position, m_rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Player::Render()
{
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

void Player::RenderShadow(D3DXMATRIX * viewMatrix, D3DXMATRIX * projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (player != nullptr && gameCamera != nullptr){
		m_model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		m_model.Draw(viewMatrix, projMatrix);
		m_model.SetDrawShadowMap(false, false);
	}
}

void Player::SilhouetteRender(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix)
{
	if (player != nullptr && gameCamera != nullptr) {
		m_model.SetSilhouetteRender(true);
		m_model.Draw(viewMatrix, projMatrix);
		m_model.SetSilhouetteRender(false);
	}
}