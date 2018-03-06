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

	bool Start();

	//�ړ�
	void Move();

	//�T��
	void Search();

	//��]
	void Turn();

	void TurnOnMoveFloor();

private:
	const float m_speed = 2.0f;
	D3DXVECTOR3 m_moveSpeed = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 m_destination;						//�ړ���̍��W
	D3DXVECTOR3 m_initPosition;						//�������W
	int m_rotationFrameCount = 0;					//��]�t���[���J�E���g
	float timer = 0.0f;								//�^�C�}�[
	bool isMove = false;							//�ړ��t���O
	D3DXVECTOR3 moveDirection = { 0.0f,0.0f,1.0f };
	int m_turnCount = 0;
};