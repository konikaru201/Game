#pragma once

#include "StoneMonsterIdle.h"
#include "StoneMonsterFollow.h"
#include "IStoneMonsterState.h"
#include "myEngine/GameObject/GameObject.h"
#include "StoneMonsterState.h"

class StoneMonsterStateMachine : public GameObject
{
public:
	//�R���X�g���N�^
	StoneMonsterStateMachine(StoneMonster* sm) :
		m_stoneMonsterIdle(sm, this),
		m_stoneMonsterFollow(sm, this)
	{
	}

	//�f�X�g���N�^
	~StoneMonsterStateMachine()
	{
	}

	//�X�V����O�Ɉ�x�����Ă΂��֐�
	bool Start();

	//�X�V
	void Update()
	{
	}

	//�X�e�[�g�؂�ւ�
	void ChangeState(StoneMonsterState::EnState nextState);

	//���
	void Release();

private:
	StoneMonsterState::EnState m_state = StoneMonsterState::enState_Invald;
	IStoneMonsterState* m_currentState = nullptr;
	StoneMonsterIdle m_stoneMonsterIdle;
	StoneMonsterFollow m_stoneMonsterFollow;
};