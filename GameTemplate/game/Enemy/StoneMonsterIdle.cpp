#include "stdafx.h"
#include "StoneMonsterIdle.h"
#include "StoneMonster.h"
#include "Player/Player.h"

void StoneMonsterIdle::Update()
{
	//プレイヤーを探す
	Search();

	//見つかっていたら
	if (GetIsFind()){
		m_sms->ChangeState(StoneMonsterState::enState_Follow);
		SetIsFind(false);
	}
}

void StoneMonsterIdle::Move()
{
	
}

void StoneMonsterIdle::Search()
{
	//プレイヤーの座標を取得
	D3DXVECTOR3 playerPos = player->GetPosition();
	//自身からプレイヤーのベクトルを計算
	D3DXVECTOR3 toPlayerPos = playerPos - m_stoneMonster->GetPosition();
	toPlayerPos.y = 0.0f;
	//プレイヤーとの距離を計算
	float length = D3DXVec3Length(&toPlayerPos);
	//自身からプレイヤーへの角度を計算
	D3DXVec3Normalize(&toPlayerPos, &toPlayerPos);
	D3DXVECTOR3 forward = m_stoneMonster->GetDirection();
	float angle = D3DXVec3Dot(&toPlayerPos, &forward);
	angle = acosf(angle);

	if (fabsf(angle) < D3DXToRadian(30.0f) && length < 12.0f)
	{
		//発見された
		SetIsFind(true);
	}
}
