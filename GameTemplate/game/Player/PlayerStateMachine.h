#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "PlayerState.h"
#include "IPlayerState.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerDead.h"
#include "PlayerGetStar.h"

class PlayerStateMachine : public GameObject {
public:
	//�R���X�g���N�^
	PlayerStateMachine(Player* pl) :
		m_playerIdle(pl, this),
		m_playerMove(pl, this),
		m_playerDead(pl, this),
		m_playerGetStar(pl, this)
	{
	}

	//�f�X�g���N�^
	~PlayerStateMachine()
	{
	}

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start();

	//�X�V
	void Update() {}

	//�X�e�[�g�؂�ւ�
	void ChangeState(PlayerState::PlState nextState);

	//���
	void Release();

private:
	PlayerState::PlState m_state = PlayerState::plState_Invald;
	IPlayerState* m_currentState = nullptr;
	PlayerIdle m_playerIdle;
	PlayerMove m_playerMove;
	PlayerDead m_playerDead;
	PlayerGetStar m_playerGetStar;
};