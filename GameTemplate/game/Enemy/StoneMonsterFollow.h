/*!
*@brief	追従ステート
*/
#pragma once

#include "IStoneMonsterState.h"

class StoneMonsterFollow : public IStoneMonsterState {
public:
	/*!
	*@brief	コンストラクタ
	*@param[in] stoneMonster ストーンモンスター
	*@param[in] sms			 ステートマシン
	*/
	StoneMonsterFollow(StoneMonster* stoneMonster, StoneMonsterStateMachine* sms) :
		IStoneMonsterState(stoneMonster, sms)
	{
	}
	/*!
	*@brief	デストラクタ
	*/
	~StoneMonsterFollow()
	{
	}
	/*!
	*@brief	更新
	*/
	void Update();
	/*!
	*@brief	移動
	*/
	void Move();
	/*!
	*@brief	探索
	*/
	void Search();
	/*!
	*@brief	回転
	*/
	void Turn();
private:
	const float m_speed = 2.0f;						//速度
	D3DXVECTOR3 m_moveSpeed = { 0.0f,0.0f,0.0f };	//移動速度
	int			m_rotationFrameCount = 0;			//回転フレームカウント
	float		m_timer = 0.0f;						//タイマー
};