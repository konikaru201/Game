#include "stdafx.h"
#include "StageMarker2.h"
#include "Scene/SceneManager.h"

StageMarker2::StageMarker2()
{
}

StageMarker2::~StageMarker2()
{
}

void StageMarker2::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation)
{
	m_modelData.LoadModelData("Assets/modelData/stageMarker2.x", NULL);
	m_model.Init(&m_modelData);
	//ライトを初期化
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
	m_model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0 }, { 1.0f,1.0f,1.0f });

	m_position = position;
	m_rotation = rotation;

	//衝突判定の初期化
	//スキンモデルからメッシュコライダーを作成する
	D3DXMATRIX* rootBoneMatrix = m_modelData.GetRootBoneWorldMatrix();
	m_meshCollider.CreateFromSkinModel(&m_model, rootBoneMatrix);

	//剛体を作るための情報を設定
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider;		//剛体のコリジョンを設定する
	rbInfo.mass = 0.0f;					//質量を0にすると動かない剛体になる
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	//剛体を作成
	m_rigidBody.Create(rbInfo);

	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
	trans.setRotation(btQuaternion(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w));

	//作成した剛体を物理ワールドに追加
	g_physicsWorld->AddRigidBody(&m_rigidBody);
}

bool StageMarker2::Start()
{
	//影を描画するフラグを立てる
	SetRenderToShadow();

	//親のワールド行列を取得
	m_parentWorldMatrix = map->GetEarthInstance()->GetWorldMatrix();
	//親のワールド行列から逆行列を作成
	D3DXMATRIX parentWorldMatrixInv;
	D3DXMatrixInverse(&parentWorldMatrixInv, NULL, &m_parentWorldMatrix);
	D3DXVec3TransformCoord(&m_childPosition, &m_position, &parentWorldMatrixInv);
	//親のワールド行列からクォータニオンを作成
	D3DXQUATERNION parentRotationMatrixInv;
	D3DXQuaternionRotationMatrix(&parentRotationMatrixInv, &parentWorldMatrixInv);
	//親から見たクォータニオンに変換
	D3DXQuaternionMultiply(&m_childRotation, &m_rotation, &parentRotationMatrixInv);

	return true;
}

void StageMarker2::Update()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		//剛体を削除
		g_physicsWorld->RemoveRigidBody(&m_rigidBody);
		return;
	}

	if (map->GetEarthInstance()->GetIsRotate()) {
		//親のワールド行列を取得
		m_parentWorldMatrix = map->GetEarthInstance()->GetWorldMatrix();
		//ワールド座標に変換する
		D3DXVec3TransformCoord(&m_position, &m_childPosition, &m_parentWorldMatrix);
		//親のワールド行列から逆行列を作成
		D3DXMATRIX parentWorldMatrixInv;
		D3DXMatrixInverse(&parentWorldMatrixInv, NULL, &m_parentWorldMatrix);
		D3DXVec3TransformCoord(&m_childPosition, &m_position, &parentWorldMatrixInv);
		//親のワールド行列からクォータニオンを作成
		D3DXQUATERNION parentRotation;
		D3DXQuaternionRotationMatrix(&parentRotation, &m_parentWorldMatrix);
		//親のクォータニオンを使って回転させる
		D3DXQuaternionMultiply(&m_rotation, &m_childRotation, &parentRotation);
		//親のワールド行列の逆行列からクォータニオンを作成
		D3DXQUATERNION parentRotationMatrixInv;
		D3DXQuaternionRotationMatrix(&parentRotationMatrixInv, &parentWorldMatrixInv);
		//親から見たクォータニオンに変換
		D3DXQuaternionMultiply(&m_childRotation, &m_rotation, &parentRotationMatrixInv);
	}

	D3DXVECTOR3 toPlayerPos = player->GetPosition() - m_position;
	float length = D3DXVec3Length(&toPlayerPos);
	if (length <= 0.8f) {
		m_UIRender = true;
		if (pad->IsTrigger(pad->enButtonA)) {
			m_decision = true;
			player->SetChangeStage(m_decision);
		}
	}
	else {
		m_UIRender = false;
	}

	if (m_decision) {
		if (player->GetAnimationEnd()) {
			m_stageChange = true;
		}
	}

	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
	trans.setRotation(btQuaternion(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w));

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f });
}

void StageMarker2::Render()
{
	m_model.SetDrawShadowMap(false, false);
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

void StageMarker2::RenderShadow(D3DXMATRIX * viewMatrix, D3DXMATRIX * projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (gameCamera != nullptr) {
		m_model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		m_model.Draw(viewMatrix, projMatrix);
		m_model.SetDrawShadowMap(false, false);
	}
}
