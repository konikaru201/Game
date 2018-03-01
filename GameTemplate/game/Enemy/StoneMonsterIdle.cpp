#include "stdafx.h"
#include "StoneMonsterIdle.h"
#include "StoneMonster.h"
#include "Player/Player.h"

void StoneMonsterIdle::Update()
{
	//�v���C���[��T��
	Search();

	//�������Ă�����
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
	//�v���C���[�̍��W���擾
	D3DXVECTOR3 playerPos = player->GetPosition();
	//���g����v���C���[�̃x�N�g�����v�Z
	D3DXVECTOR3 toPlayerPos = playerPos - m_stoneMonster->GetPosition();
	toPlayerPos.y = 0.0f;
	//�v���C���[�Ƃ̋������v�Z
	float length = D3DXVec3Length(&toPlayerPos);
	//���g����v���C���[�ւ̊p�x���v�Z
	D3DXVec3Normalize(&toPlayerPos, &toPlayerPos);
	D3DXVECTOR3 forward = m_stoneMonster->GetDirection();
	float angle = D3DXVec3Dot(&toPlayerPos, &forward);
	angle = acosf(angle);

	if (fabsf(angle) < D3DXToRadian(30.0f) && length < 12.0f)
	{
		//�������ꂽ
		SetIsFind(true);
	}
}
