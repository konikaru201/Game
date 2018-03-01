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
		//同じステートに遷移
		return;
	}
	//ゲームオブジェクトから外すフラグを立てる
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

	//ゲームオブジェクトにから外れないようにフラグを戻す
	if (m_currentState != nullptr) {
		m_currentState->SetIsChangeState(false);
	}

	goMgr->AddGameObject(m_currentState);
}
