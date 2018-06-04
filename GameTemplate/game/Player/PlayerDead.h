#pragma once

#include "IPlayerState.h"

class PlayerDead : public IPlayerState{
public:
	//�R���X�g���N�^
	PlayerDead(Player* player, PlayerStateMachine* psm) :
		IPlayerState(player, psm)
	{
	}

	//�f�X�g���N�^
	~PlayerDead()
	{
	}

	//�X�V
	void Update();

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start();

	//���S����
	void Dead();
private:
	float m_timer = 0.0f;			//�^�C�}�[
	bool m_deadTimerFlag = false;	//���S��ɃV�[����؂�ւ��邽�߂̃t���O
};