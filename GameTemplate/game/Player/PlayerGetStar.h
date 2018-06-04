#pragma once

#include "IPlayerState.h"

class PlayerGetStar : public IPlayerState {
public:
	//コンストラクタ
	PlayerGetStar(Player* player, PlayerStateMachine* psm) :
		IPlayerState(player, psm)
	{
	}

	//デストラクタ
	~PlayerGetStar()
	{
	}

	//更新
	void Update();
	
	//更新する前に一度だけ呼ばれる
	bool Start();

private:
	bool animationEnd = false;
};