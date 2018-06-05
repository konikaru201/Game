/*!
*@brief	待機ステート
*/
#pragma once

#include "IStoneMonsterState.h"

class StoneMonsterIdle : public IStoneMonsterState {
public:
	/*!
	*@brief	コンストラクタ
	*@param[in] stoneMonster ストーンモンスター
	*@param[in] sms			 ステートマシン
	*/
	StoneMonsterIdle(StoneMonster* stoneMonster, StoneMonsterStateMachine* sms) :
		IStoneMonsterState(stoneMonster, sms)
	{
	}
	/*!
	*@brief	デストラクタ
	*/
	~StoneMonsterIdle()
	{
	}
	/*!
	*@brief	更新
	*/
	void Update();
	/*!
	*@brief	更新する前に一度だけ呼ばれる
	*/
	bool Start();
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
	/*!
	*@brief	移動床上での回転
	*/
	void TurnOnMoveFloor();
private:
	const float m_speed = 2.0f;							//速度
	D3DXVECTOR3 m_moveSpeed = { 0.0f,0.0f,0.0f };		//移動速度
	D3DXVECTOR3 m_destination;							//移動先の座標
	D3DXVECTOR3 m_initPosition;							//初期座標
	int			m_rotationFrameCount = 0;				//回転フレームカウント
	float		m_timer = 0.0f;							//タイマー
	bool		m_isMove = false;						//移動フラグ
	D3DXVECTOR3 m_moveDirection = { 0.0f,0.0f,1.0f };	//移動方向
	int			m_turnCount = 0;						//回転フレームカウント(移動床上)
};