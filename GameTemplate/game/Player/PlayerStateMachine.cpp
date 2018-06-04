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

	//ゲームオブジェクトから外れないようにフラグを戻す
	if (m_currentState != nullptr) {
		m_currentState->SetIsChangeState(false);
	}

	goMgr->AddGameObject(m_currentState);
}

void PlayerStateMachine::Release()
{
	//シーン切り替え時に現在のステートをゲームオブジェクトから外す
	m_currentState->SetIsChangeState(true);
}
