#pragma once

#include "IStoneMonsterState.h"

class StoneMonsterIdle : public IStoneMonsterState {
public:
	//�R���X�g���N�^
	StoneMonsterIdle(StoneMonster* stoneMonster, StoneMonsterStateMachine* sms) :
		IStoneMonsterState(stoneMonster, sms)
	{
	}

	//�f�X�g���N�^
	~StoneMonsterIdle()
	{
	}

	//�X�V
	void Update();

	//�ړ�
	void Move();

	//�T��
	void Search();

private:
	D3DXVECTOR3 m_moveSpeed = { 0.0f,0.0f,0.0f };
};