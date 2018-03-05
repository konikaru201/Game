#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Physics/CharacterController.h"
#include "StoneMonsterStateMachine.h"

class StoneMonster : public GameObject
{
public:
	StoneMonster();
	~StoneMonster();

	//初期化
	//pos	座標
	//rot	回転
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	bool Start();

	//更新
	void Update();

	//描画
	void Render();

	//影の描画
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);

	//座標を取得
	const D3DXVECTOR3& GetPosition()
	{
		return m_position;
	}

	//座標を設定
	void SetPosition(const D3DXVECTOR3& position)
	{
		m_position = position;
	}

	//回転を取得
	const D3DXQUATERNION& GetRotation()
	{
		return m_rotation;
	}

	//回転を設定
	void SetRotation(const D3DXQUATERNION& rotation)
	{
		m_rotation = rotation;
	}

	//モデルの向きを取得
	const D3DXVECTOR3& GetDirection()
	{
		D3DXMATRIX matrix = m_model.GetWorldMatrix();
		m_direction.x = matrix.m[2][0];
		m_direction.y = matrix.m[2][1];
		m_direction.z = matrix.m[2][2];
		D3DXVec3Normalize(&m_direction, &m_direction);
		return m_direction;
	}

	//移動速度を取得
	const D3DXVECTOR3& GetMoveSpeed()
	{
		return m_characterController.GetMoveSpeed();
	}

	//移動速度を設定
	void SetMoveSpeed(const D3DXVECTOR3& moveSpeed)
	{
		m_characterController.SetMoveSpeed(moveSpeed);
	}

private:
	SkinModel					m_model;							//スキンモデル
	SkinModelData				m_modelData;						//スキンモデルデータ
	Light						m_light;							//ライト
	D3DXVECTOR3					m_position;							//座標
	D3DXQUATERNION				m_rotation;							//回転
	D3DXVECTOR3					m_direction;						//向き
	Animation					m_animation;						//アニメーション
	D3DXVECTOR3					m_moveSpeed = { 0.0f,0.0f,0.0f };	//移動速度
	CharacterController			m_characterController;				//キャラクターコントローラー
	StoneMonsterStateMachine	m_stoneMonsterStateMachine;			//ステートマシン
};