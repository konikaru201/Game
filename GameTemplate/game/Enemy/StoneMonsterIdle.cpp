#include "stdafx.h"
#include "StoneMonsterIdle.h"
#include "StoneMonster.h"
#include "Player/Player.h"

void StoneMonsterIdle::Update()
{
	//�v���C���[��T��
	Search();

	//�ړ�
	Move();

	//�������Ă�����
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
	//�v���C���[�̍��W���擾
	D3DXVECTOR3 playerPos = player->GetPosition();
	//���g����v���C���[�̃x�N�g�����v�Z
	D3DXVECTOR3 toPlayerDir = playerPos - m_stoneMonster->GetPosition();
	//�v���C���[�Ƃ̋������v�Z
	float length = D3DXVec3Length(&toPlayerDir);
	toPlayerDir.y = 0.0f;
	//���g����v���C���[�ւ̊p�x���v�Z
	D3DXVec3Normalize(&toPlayerDir, &toPlayerDir);
	D3DXVECTOR3 forward = m_stoneMonster->GetDirection();
	float angle = D3DXVec3Dot(&toPlayerDir, &forward);
	angle = acosf(angle);

	if (fabsf(angle) < D3DXToRadian(30.0f) && length < 6.0f || length < 3.0f)
	{
		//�������ꂽ
		SetIsFind(true);
	}
}

void StoneMonsterIdle::Turn()
{
}
