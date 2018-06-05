/*!
*@brief	待機ステート
*/
#pragma once

#include "IPlayerState.h"

class PlayerIdle : public IPlayerState {
public:
	/*!
	*@brief	コンストラクタ
	* @param[in]	player		プレイヤー
	* @param[in]	psm			ステートマシン
	*/
	PlayerIdle(Player* player, PlayerStateMachine* psm) :
		IPlayerState(player, psm)
	{
	}
	/*!
	*@brief	デストラクタ
	*/
	~PlayerIdle()
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
};