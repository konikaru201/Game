#include "stdafx.h"
#include "StoneMonsterFollow.h"
#include "StoneMonster.h"
#include "Player/Player.h"
#include "myEngine/Timer/Timer.h"

void StoneMonsterFollow::Update()
{
	//プレイヤーを探す
	Search();

	//見つかっている
	if (GetIsFind())
	{
		//移動
		Move();
		//回転
		Turn();
	}

	//見失ったら
	if (!GetIsFind()) {
		m_sms->ChangeState(StoneMonsterState::enState_Idle);
	}
}

void StoneMonsterFollow::Move()
{
	m_moveSpeed = m_stoneMonster->GetMoveSpeed();
	D3DXVECTOR3 AxisZ = { 0.0f,0.0f,1.0f };
	//プレイヤーの座標を取得
	D3DXVECTOR3 playerPos = player->GetPosition();
	//自身からプレイヤーのベクトルを計算
	D3DXVECTOR3 toPlayerDir = playerPos - m_stoneMonster->GetPosition();
	D3DXVec3Normalize(&toPlayerDir, &toPlayerDir);
	m_moveSpeed.x = toPlayerDir.x * m_speed;
	m_moveSpeed.z = toPlayerDir.z * m_speed;

	if (m_stoneMonster->GetIsOnMoveFloor() || m_stoneMonster->GetIsOnMoveFloor2())
	{
		D3DXVECTOR3 position = m_stoneMonster->GetPosition();
		D3DXVECTOR3 toMoveFloorPosition;
		if (m_stoneMonster->GetIsOnMoveFloor()) {
			toMoveFloorPosition = m_stoneMonster->GetMoveFloorPosition() - position;
		}
		else {
			toMoveFloorPosition = m_stoneMonster->GetMoveFloor2Position() - position;
		}

		float length = D3DXVec3Length(&toMoveFloorPosition);
		if (length >= 2.4f) {
			timer += Timer::GetFrameDeltaTime();
			if (timer >= 2.0f) {
				D3DXVec3Normalize(&toMoveFloorPosition, &toMoveFloorPosition);
				toMoveFloorPosition *= m_speed;
				m_moveSpeed.x = toMoveFloorPosition.x;
				m_moveSpeed.z = toMoveFloorPosition.z;
			}
			else {
				m_moveSpeed.x = 0.0f;
				m_moveSpeed.z = 0.0f;
			}
		}
		else {
			D3DXVECTOR3 AxisZ = { 0.0f,0.0f,1.0f };
			//プレイヤーの座標を取得
			D3DXVECTOR3 playerPos = player->GetPosition();
			//自身からプレイヤーのベクトルを計算
			D3DXVECTOR3 toPlayerDir = playerPos - m_stoneMonster->GetPosition();
			D3DXVec3Normalize(&toPlayerDir, &toPlayerDir);
			m_moveSpeed.x = toPlayerDir.x * m_speed;
			m_moveSpeed.z = toPlayerDir.z * m_speed;
		}
	}

	m_stoneMonster->SetMoveSpeed(m_moveSpeed);
}

void StoneMonsterFollow::Search()
{
	//プレイヤーの座標を取得
	D3DXVECTOR3 playerPos = player->GetPosition();
	//自身からプレイヤーのベクトルを計算
	D3DXVECTOR3 toPlayerDir = playerPos - m_stoneMonster->GetPosition();
	//プレイヤーとの距離を計算
	float length = D3DXVec3Length(&toPlayerDir);
	toPlayerDir.y = 0.0f;
	//自身からプレイヤーへの角度を計算
	D3DXVec3Normalize(&toPlayerDir, &toPlayerDir);
	D3DXVECTOR3 forward = m_stoneMonster->GetDirection();
	float angle = D3DXVec3Dot(&toPlayerDir, &forward);
	angle = acosf(angle);

	if (fabsf(angle) < D3DXToRadian(30.0f) && length < 8.0f || length < 5.0f)
	{
		//見つかった
		SetIsFind(true);
	}
	else {
		//見失った
		SetIsFind(false);
	}
}

void StoneMonsterFollow::Turn()
{
	D3DXQUATERNION rot;
	D3DXQuaternionIdentity(&rot);
	m_rotationFrameCount++;
	//モデルの前方向を取得
	D3DXVECTOR3 forward = m_stoneMonster->GetDirection();
	D3DXVec3Normalize(&forward, &forward);
	//プレイヤーの座標を取得
	D3DXVECTOR3 playerPos = player->GetPosition();
	//自身からプレイヤーのベクトルを計算
	D3DXVECTOR3 toPlayerDir = playerPos - m_stoneMonster->GetPosition();
	toPlayerDir.y = 0.0f;
	D3DXVec3Normalize(&toPlayerDir, &toPlayerDir);
	float angle = D3DXVec3Dot(&forward, &toPlayerDir);
	if (angle < -1.0f)
	{
		angle = -1.0f;
	}
	if (angle > 1.0f)
	{
		angle = 1.0f;
	}
	angle = acosf(angle);
	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &forward, &toPlayerDir);
	if (Cross.y < 0.0f) {
		angle *= -1.0f;
	}
	angle /= 5;
	if (m_rotationFrameCount <= 5) {
		D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);
		D3DXQUATERNION rotation = m_stoneMonster->GetRotation();
		D3DXQuaternionMultiply(&rotation, &rotation, &rot);
		m_stoneMonster->SetRotation(rotation);
	}
	else {
		m_rotationFrameCount = 0;
	}
}
