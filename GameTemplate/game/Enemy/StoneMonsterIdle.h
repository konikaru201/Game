#pragma once

#include "IStoneMonsterState.h"

class StoneMonsterIdle : public IStoneMonsterState {
public:
	//コンストラクタ
	StoneMonsterIdle(StoneMonster* stoneMonster, StoneMonsterStateMachine* sms) :
		IStoneMonsterState(stoneMonster, sms)
	{
	}

	//デストラクタ
	~StoneMonsterIdle()
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