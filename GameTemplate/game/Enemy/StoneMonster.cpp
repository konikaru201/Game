#include "stdafx.h"
#include "StoneMonster.h"
#include "Scene/SceneManager.h"
#include "Player/Player.h"
#include "myEngine/sound/SoundSource.h"

StoneMonster::StoneMonster() :
	m_stoneMonsterStateMachine(this)
{
}

StoneMonster::~StoneMonster()
{
}

void StoneMonster::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	//モデルの初期化
	m_modelData.LoadModelData("Assets/modelData/StoneMonster.x", NULL);
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

	m_position = pos;
	m_rotation = rot;
	m_scale = { 1.0f,1.0f,1.0f };

	//剛体の作成
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(0.3f, 0.4f);
	m_characterController.Init(coll, m_position);
}

bool StoneMonster::Start()
{
	//影を描画するフラグを立てる
	SetRenderToShadow();

	goMgr->AddGameObject(&m_stoneMonsterStateMachine);

	//一番近い移動床のワールド行列を取得
	if (!map->GetMoveFloorList().empty()){
		m_parentWorldMatrix = map->GetMoveFloorWorldMatrix(m_position);
		m_moveFloorPosition = map->GetMoveFloorPosition(m_position);
	}
	if (!map->GetMoveFloor2List().empty()) {
		m_secondParentWorldMatrix = map->GetMoveFloor2WorldMatrix(m_position);
		m_moveFloor2Position = map->GetMoveFloor2Position(m_position);
	}

	//最初に親のワールド行列から自身のローカル座標を計算
	//キャラクターコントローラーを実行
	m_characterController.Execute();
	if (m_characterController.IsOnMoveFloor()) {
		//親のワールド行列から逆行列を生成
		D3DXMATRIX parentWorldMatrixInv;
		D3DXMatrixInverse(&parentWorldMatrixInv, NULL, &m_parentWorldMatrix);
		D3DXVec3TransformCoord(&m_childPosition, &m_position, &parentWorldMatrixInv);
		m_moveFloorHit = true;
	}
	if (m_characterController.IsOnMoveFloor2()) {
		//親のワールド行列から逆行列を生成
		D3DXMATRIX secondParentWorldMatrixInv;
		D3DXMatrixInverse(&secondParentWorldMatrixInv, NULL, &m_secondParentWorldMatrix);
		D3DXVec3TransformCoord(&m_secondChildPosition, &m_position, &secondParentWorldMatrixInv);
		m_moveFloor2Hit = true;
	}

	return true;
}

void StoneMonster::Update()
{
	//シーン切り替え時
	if (sceneManager->GetChangeSceneFlag() || m_deadTimer >= 0.5f)
	{
		//状態クラスの死亡フラグを立てる
		m_stoneMonsterStateMachine.SetIsChangeState(true);
		m_stoneMonsterStateMachine.Release();
		//死亡フラグを立てる
		SetisDead();
		//剛体を削除
		m_characterController.RemoveRigidBoby();
		return;
	}	

	//踏まれたら死亡タイマーをカウント
	if (m_isStepOn) {
		m_deadTimer += Timer::GetFrameDeltaTime();
	}

	if(!player->GetHitEnemy()){
		//プレイヤーとの当たり判定
		D3DXVECTOR3 playerPos = player->GetPosition();
		D3DXVECTOR3 toPlayerPos = playerPos - m_position;
		float length = D3DXVec3Length(&toPlayerPos);
		if (length <= 1.0f) {
			D3DXVECTOR3 playerMoveSpeed = player->GetMoveSpeed();
			D3DXVECTOR3 toPlayerPosY = { 0.0f,toPlayerPos.y,0.0f };
			D3DXVECTOR3 toPlayerPosXZ = { toPlayerPos.x,0.0f,toPlayerPos.z };
			float lengthY = D3DXVec3Length(&toPlayerPosY);
			float lengthXZ = D3DXVec3Length(&toPlayerPosXZ);
			if (toPlayerPos.y > 0.0f && lengthY <= 0.5f && lengthXZ <= 0.6f) {
				player->SetTreadOnEnemy(true);
				m_isStepOn = true;
				m_scale.y = 0.1f;

				CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
				SE->Init("Assets/sound/Humituke.wav");
				SE->Play(false);
			}
			else if (lengthY <= 0.4f && lengthXZ <= 0.7f) {
				player->SetHitEnemy(true);
				m_isHitPlaer = true;
			}
		}
	}

	//毎フレーム親のワールド行列を更新
	if (m_moveFloorHit == true && !map->GetMoveFloorList().empty()){
		m_parentWorldMatrix = map->GetMoveFloorWorldMatrix(m_position);
		m_moveFloorPosition = map->GetMoveFloorPosition(m_position);
	}
	else if (m_moveFloor2Hit == true && !map->GetMoveFloor2List().empty()) {
		m_secondParentWorldMatrix = map->GetMoveFloor2WorldMatrix(m_position);
		m_moveFloor2Position = map->GetMoveFloor2Position(m_position);
	}

	//移動床に当たっている
	if (m_moveFloorHit) {
		//ワールド座標に変換する
		D3DXVec3TransformCoord(&m_position, &m_childPosition, &m_parentWorldMatrix);
		m_characterController.SetPosition(m_position);

		m_characterController.SetMoveSpeed(m_moveSpeed);
		//キャラクターコントローラーを実行D3D
		m_characterController.Execute();
		//座標を設定
		m_position = m_characterController.GetPosition();

		//親から見たプレイヤーの座標を更新
		D3DXMATRIX worldMatrixInv;
		D3DXMatrixInverse(&worldMatrixInv, NULL, &m_parentWorldMatrix);
		D3DXVec3TransformCoord(&m_childPosition, &m_position, &worldMatrixInv);
	}
	else if (m_moveFloor2Hit){
		//ワールド座標に変換する
		D3DXVec3TransformCoord(&m_position, &m_secondChildPosition, &m_secondParentWorldMatrix);
		m_characterController.SetPosition(m_position);

		m_characterController.SetMoveSpeed(m_moveSpeed);
		//キャラクターコントローラーを実行
		m_characterController.Execute();
		//座標を設定
		m_position = m_characterController.GetPosition();

		//親から見た座標を更新
		D3DXMATRIX worldMatrixInv;
		D3DXMatrixInverse(&worldMatrixInv, NULL, &m_secondParentWorldMatrix);
		D3DXVec3TransformCoord(&m_secondChildPosition, &m_position, &worldMatrixInv);
	}
	else {
		m_characterController.SetMoveSpeed(m_moveSpeed);
		//キャラクターコントローラーを実行
		m_characterController.Execute();
		//座標を設定
		m_position = m_characterController.GetPosition();
	}

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void StoneMonster::Render()
{
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

void StoneMonster::RenderShadow(D3DXMATRIX * viewMatrix, D3DXMATRIX * projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (gameCamera != nullptr) {
		m_model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		m_model.Draw(viewMatrix, projMatrix);
		m_model.SetDrawShadowMap(false, false);
	}
}
