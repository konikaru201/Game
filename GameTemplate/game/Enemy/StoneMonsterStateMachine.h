#pragma once

#include "StoneMonsterIdle.h"
#include "StoneMonsterFollow.h"
#include "IStoneMonsterState.h"
#include "myEngine/GameObject/GameObject.h"
#include "StoneMonsterState.h"

class StoneMonsterStateMachine : public GameObject
{
public:
	//コンストラクタ
	StoneMonsterStateMachine(StoneMonster* sm) :
		m_stoneMonsterIdle(sm, this),
		m_stoneMonsterFollow(sm, this)
	{
	}

	//デストラクタ
	~StoneMonsterStateMachine()
	{
	}

	//更新する前に一度だけ呼ばれる関数
	bool Start();

	//更新
	void Update()
	{
	}

	//ステート切り替え
	void ChangeState(StoneMonsterState::EnState nextState);

	//解放
	void Release();

private:
	StoneMonsterState::EnState m_state = StoneMonsterState::enState_Invald;
	IStoneMonsterState* m_currentState = nullptr;
	StoneMonsterIdle m_stoneMonsterIdle;
	StoneMonsterFollow m_stoneMonsterFollow;
};