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

	bool Start();

	//移動
	void Move();

	//探索
	void Search();

	//回転
	void Turn();

	void TurnOnMoveFloor();

private:
	const float m_speed = 2.0f;
	D3DXVECTOR3 m_moveSpeed = { 0.0f,0.0f,0.0f };
	D3DXVECTOR3 m_destination;						//移動先の座標
	D3DXVECTOR3 m_initPosition;						//初期座標
	int m_rotationFrameCount = 0;					//回転フレームカウント
	float timer = 0.0f;								//タイマー
	bool isMove = false;							//移動フラグ
	D3DXVECTOR3 moveDirection = { 0.0f,0.0f,1.0f };
	int m_turnCount = 0;
};