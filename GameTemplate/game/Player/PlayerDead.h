#pragma once

#include "IPlayerState.h"

class PlayerDead : public IPlayerState{
public:
	//コンストラクタ
	PlayerDead(Player* player, PlayerStateMachine* psm) :
		IPlayerState(player, psm)
	{
	}

	//デストラクタ
	~PlayerDead()
	{
	}

	//更新
	void Update();

	//更新する前に一度だけ呼ばれる
	bool Start();

	//死亡処理
	void Dead();
private:
	float m_timer = 0.0f;			//タイマー
	bool m_deadTimerFlag = false;	//死亡後にシーンを切り替えるためのフラグ
};