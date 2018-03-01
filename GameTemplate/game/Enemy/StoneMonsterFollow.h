#pragma once

#include "IStoneMonsterState.h"

class StoneMonsterFollow : public IStoneMonsterState {
public:
	//コンストラクタ
	StoneMonsterFollow(StoneMonster* stoneMonster, StoneMonsterStateMachine* sms) :
		IStoneMonsterState(stoneMonster, sms)
	{
	}

	//デストラクタ
	~StoneMonsterFollow()
	{
	}

	//更新
	void Update();

	//移動
	void Move();

	//探索
	void Search();

private:
	D3DXVECTOR3 m_moveSpeed = { 0.0f,0.0f,0.0f };
};