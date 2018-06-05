/*!
*@brief	ストーンモンスターのステートマシン
*/
#pragma once

#include "StoneMonsterIdle.h"
#include "StoneMonsterFollow.h"
#include "IStoneMonsterState.h"
#include "myEngine/GameObject/GameObject.h"
#include "StoneMonsterState.h"

class StoneMonsterStateMachine : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	* @param[in]	sm		ストーンモンスター
	*/
	StoneMonsterStateMachine(StoneMonster* sm) :
		m_stoneMonsterIdle(sm, this),
		m_stoneMonsterFollow(sm, this)
	{
	}
	/*!
	*@brief	デストラクタ
	*/
	~StoneMonsterStateMachine()
	{
	}
	/*!
	*@brief	更新する前に一度だけ呼ばれる
	*/
	bool Start();
	/*!
	*@brief	更新
	*/
	void Update()
	{
	}
	/*!
	*@brief	ステート切り替え
	* @param[in]	nextState		次のステート
	*/
	void ChangeState(StoneMonsterState::EnState nextState);
	/*!
	*@brief	解放
	*/
	void Release();
private:
	StoneMonsterState::EnState	m_state = StoneMonsterState::enState_Invald;	//ストーンモンスターの状態
	IStoneMonsterState*			m_currentState = nullptr;						//現在の状態
	StoneMonsterIdle			m_stoneMonsterIdle;								//待機ステート
	StoneMonsterFollow			m_stoneMonsterFollow;							//追従ステート
};