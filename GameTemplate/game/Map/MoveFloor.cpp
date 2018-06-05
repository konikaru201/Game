#include "stdafx.h"
#include "MoveFloor.h"
#include "Scene/SceneManager.h"
#include "myEngine/Physics/CollisionAttr.h"
#include "myEngine/Timer/Timer.h"
#include "Player/Player.h"

MoveFloor::MoveFloor() 
{
}

MoveFloor::~MoveFloor()
{
}

void MoveFloor::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	m_modelData.LoadModelData("Assets/modelData/MoveFloor_1.x", NULL);
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
	m_moveSpeed = { 0.05f,0.0f,0.0f };

	//衝突判定の初期化
	//スキンモデルからボックスコライダーを作成する
	BoxCollider* boxCollider = new BoxCollider;
	boxCollider->Create(D3DXVECTOR3(2.5f, 0.41f, 2.5f));

	//剛体を作るための情報を設定
	RigidBodyInfo rbInfo;
	rbInfo.collider = boxCollider;		//剛体のコリジョンを設定する
	rbInfo.mass = 0.0f;					//質量を0にすると動かない剛体になる
	rbInfo.pos = m_position;
	rbInfo.rot = m_rotation;
	//剛体を作成
	m_rigidBody.Create(rbInfo);

	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));

	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_MoveFloor);
	m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	m_rigidBody.GetBody()->setActivationState(DISABLE_DEACTIVATION);

	//作成した剛体を物理ワールドに追加
	g_physicsWorld->AddRigidBody(&m_rigidBody);
}

bool MoveFloor::Start()
{
	return true;
}

void MoveFloor::PreUpdate()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		//剛体を削除
		g_physicsWorld->RemoveRigidBody(&m_rigidBody);
		return;
	}

	Move();

	if (m_moveFlag) {
		player->SetMoveFloorSpeed(m_moveSpeed);
	}
	else {
		player->SetMoveFloorSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f });
}
void MoveFloor::Update()
{	
	
}

void MoveFloor::Move()
{
	m_timer += Timer::GetFrameDeltaTime();
	m_moveFlag = true;
	if (m_timer >= 10.0f) {
		m_moveSpeed *= -1.0f;
		m_timer = 0.0f;
	}
	if (m_timer >= 2.0f)
	{
		m_position += m_moveSpeed;
	}
	else
	{
		m_moveFlag = false;
	}
}

void MoveFloor::Render()
{
	m_model.SetDrawShadowMap(false, true);
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}