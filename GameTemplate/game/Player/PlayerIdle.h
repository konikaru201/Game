#pragma once

#include "IPlayerState.h"

class PlayerIdle : public IPlayerState {
public:
	PlayerIdle(Player* player, PlayerStateMachine* psm) :
		IPlayerState(player, psm)
	{
	}

	~PlayerIdle()
	{
	}

	void Update();

	bool Start();
};