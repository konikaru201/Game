/*!
*@brief	死亡ステート
*/
#pragma once

#include "IPlayerState.h"

class PlayerDead : public IPlayerState{
public:
	/*!
	*@brief	コンストラクタ
	* @param[in]	player		プレイヤー
	* @param[in]	psm			ステートマシン
	*/
	PlayerDead(Player* player, PlayerStateMachine* psm) :
		IPlayerState(player, psm)
	{
	}
	/*!
	*@brief	デストラクタ
	*/
	~PlayerDead()
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
	*@brief	死亡処理
	*/
	void Dead();
private:
	float m_timer = 0.0f;			//タイマー
	bool m_deadTimerFlag = false;	//死亡後にシーンを切り替えるためのフラグ
};