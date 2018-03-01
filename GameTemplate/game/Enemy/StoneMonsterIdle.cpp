#include "stdafx.h"
#include "StoneMonsterIdle.h"
#include "StoneMonster.h"
#include "Player/Player.h"

void StoneMonsterIdle::Update()
{
	//プレイヤーを探す
	Search();

	//移動
	Move();

	//見つかっていたら
	if (GetIsFind()){
		m_sms->ChangeState(StoneMonsterState::enState_Follow);
		SetIsFind(false);
	}
}

void StoneMonsterIdle::Move()
{
	m_moveSpeed = m_stoneMonster->GetMoveSpeed();
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_stoneMonster->SetMoveSpeed(m_moveSpeed);
}

void StoneMonsterIdle::Search()
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

	if (fabsf(angle) < D3DXToRadian(30.0f) && length < 6.0f || length < 3.0f)
	{
		//発見された
		SetIsFind(true);
	}
}

void StoneMonsterIdle::Turn()
{
}
