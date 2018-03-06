#pragma once

#include "IStoneMonsterState.h"

class StoneMonsterFollow : public IStoneMonsterState {
public:
	//�R���X�g���N�^
	StoneMonsterFollow(StoneMonster* stoneMonster, StoneMonsterStateMachine* sms) :
		IStoneMonsterState(stoneMonster, sms)
	{
	}

	//�f�X�g���N�^
	~StoneMonsterFollow()
	{
	}

	//�X�V
	void Update();

	//�ړ�
	void Move();

	//�T��
	void Search();

	//��]
	void Turn();

private:
	const float m_speed = 2.0f;
	D3DXVECTOR3 m_moveSpeed = { 0.0f,0.0f,0.0f };
	int m_rotationFrameCount = 0;					//��]�t���[���J�E���g
	float timer = 0.0f;
};