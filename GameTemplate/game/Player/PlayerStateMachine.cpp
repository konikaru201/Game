#include "stdafx.h"
#include "PlayerStateMachine.h"
#include "myEngine/GameObject/GameObjectManager.h"

bool PlayerStateMachine::Start()
{
	ChangeState(PlayerState::plState_Idle);
	return true;
}

void PlayerStateMachine::ChangeState(PlayerState::PlState nextState)
{
	if (m_state == nextState) {
		//�����X�e�[�g�ɑJ��
		return;
	}
	//�Q�[���I�u�W�F�N�g����O���t���O�𗧂Ă�
	if (m_currentState != nullptr) {
		m_currentState->SetIsChangeState(true);
	}
	m_state = nextState;

	switch (m_state)
	{
	case PlayerState::plState_Idle:
		m_currentState = &m_playerIdle;
		break;
	case PlayerState::plState_Move:
		m_currentState = &m_playerMove;
		break;
	case PlayerState::plState_Dead:
		m_currentState = &m_playerDead;
		break;
	case PlayerState::plState_GetStar:
		m_currentState = &m_playerGetStar;
		break;
	}

	//�Q�[���I�u�W�F�N�g����O��Ȃ��悤�Ƀt���O��߂�
	if (m_currentState != nullptr) {
		m_currentState->SetIsChangeState(false);
	}

	goMgr->AddGameObject(m_currentState);
}

void PlayerStateMachine::Release()
{
	//�V�[���؂�ւ����Ɍ��݂̃X�e�[�g���Q�[���I�u�W�F�N�g����O��
	m_currentState->SetIsChangeState(true);
}
