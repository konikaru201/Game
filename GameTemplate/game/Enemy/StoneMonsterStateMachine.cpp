#include "stdafx.h"
#include "StoneMonsterStateMachine.h"
#include "myEngine/GameObject/GameObjectManager.h"

bool StoneMonsterStateMachine::Start()
{
	ChangeState(StoneMonsterState::enState_Idle);
	return true;
}

void StoneMonsterStateMachine::ChangeState(StoneMonsterState::EnState nextState)
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
	case StoneMonsterState::enState_Idle:
		m_currentState = &m_stoneMonsterIdle;
		break;
	case StoneMonsterState::enState_Follow:
		m_currentState = &m_stoneMonsterFollow;
		break;
	}

	//�Q�[���I�u�W�F�N�g�ɂ���O��Ȃ��悤�Ƀt���O��߂�
	if (m_currentState != nullptr) {
		m_currentState->SetIsChangeState(false);
	}

	goMgr->AddGameObject(m_currentState);
}
