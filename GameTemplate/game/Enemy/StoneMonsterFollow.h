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

	//回転
	void Turn();

private:
	const float m_speed = 2.0f;
	D3DXVECTOR3 m_moveSpeed = { 0.0f,0.0f,0.0f };
	int m_rotationFrameCount = 0;					//回転フレームカウント
	float timer = 0.0f;
};