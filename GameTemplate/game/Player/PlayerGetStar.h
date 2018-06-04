#pragma once

#include "IPlayerState.h"

class PlayerGetStar : public IPlayerState {
public:
	//�R���X�g���N�^
	PlayerGetStar(Player* player, PlayerStateMachine* psm) :
		IPlayerState(player, psm)
	{
	}

	//�f�X�g���N�^
	~PlayerGetStar()
	{
	}

	//�X�V
	void Update();
	
	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start();

private:
	bool animationEnd = false;
};