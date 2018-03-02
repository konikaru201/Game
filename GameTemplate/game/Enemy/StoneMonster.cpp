#include "stdafx.h"
#include "StoneMonster.h"
#include "Scene/SceneManager.h"

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

	//剛体の作成
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(0.4f, 0.8f);
	m_characterController.Init(coll, m_position);
}

bool StoneMonster::Start()
{
	//影を描画するフラグを立てる
	SetRenderToShadow();

	goMgr->AddGameObject(&m_stoneMonsterStateMachine);

	return true;
}

void StoneMonster::Update()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		m_stoneMonsterStateMachine.SetIsChangeState(true);
		m_stoneMonsterStateMachine.Release();

		SetisDead();
		//剛体を削除
		//g_physicsWorld->RemoveRigidBody(&m_rigidBody);
		m_characterController.RemoveRigidBoby();
		return;
	}	

	//if (!m_characterController.IsOnGround()) {
	//	m_characterController.SetMoveSpeed(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//}

	//キャラクターコントローラーを実行
	m_characterController.Execute();
	//座標を設定
	m_position = m_characterController.GetPosition();

	m_model.UpdateWorldMatrix(m_position, m_rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));

}

void StoneMonster::Render()
{
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetViewProjectionMatrix());
}

void StoneMonster::RenderShadow(D3DXMATRIX * viewMatrix, D3DXMATRIX * projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (gameCamera != nullptr) {
		m_model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		m_model.Draw(viewMatrix, projMatrix);
		m_model.SetDrawShadowMap(false, false);
	}
}
