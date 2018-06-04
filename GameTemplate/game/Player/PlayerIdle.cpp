#include "stdafx.h"
#include "PlayerIdle.h"
#include "myEngine/HID/Pad.h"
#include "Player.h"

void PlayerIdle::Update()
{
	D3DXVECTOR3 moveSpeed = m_player->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	//�v���C���[�̈ړ����x��ݒ�
	m_player->SetMoveSpeed(moveSpeed);

	//�����A�j���[�V������ݒ�
	m_currentAnim = AnimationStand;
	m_player->SetCurrentAnim(m_currentAnim);

	if (pad->GetLStickXF() != 0.0f || pad->GetLStickYF() != 0.0f || pad->IsTrigger(pad->enButtonA)) {
		m_psm->ChangeState(PlayerState::plState_Move);
	}
	else if (m_player->GetHitEnemy() || m_player->GetFallPlayer()) {
		m_psm->ChangeState(PlayerState::plState_Dead);
	}
}

bool PlayerIdle::Start()
{
	return true;
}
