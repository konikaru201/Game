/*!
*@brief	スター獲得ステート
*/
#pragma once

#include "IPlayerState.h"

class PlayerGetStar : public IPlayerState {
public:
	/*!
	*@brief	コンストラクタ
	* @param[in]	player		プレイヤー
	* @param[in]	psm			ステートマシン
	*/
	PlayerGetStar(Player* player, PlayerStateMachine* psm) :
		IPlayerState(player, psm)
	{
	}
	/*!
	*@brief	デストラクタ
	*/
	~PlayerGetStar()
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
private:
	bool m_animationEnd = false;	//アニメーションの終了フラグ
};