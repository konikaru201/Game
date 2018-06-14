/*!
*@brief	ステージ変更ステート
*/
#pragma once

#include "IPlayerState.h"

class PlayerChangeStage : public IPlayerState {
public:
	/*!
	*@brief	コンストラクタ
	* @param[in]	player		プレイヤー
	* @param[in]	psm			ステートマシン
	*/
	PlayerChangeStage(Player* player, PlayerStateMachine* psm) :
		IPlayerState(player, psm)
	{
	}
	/*!
	*@brief	デストラクタ
	*/
	~PlayerChangeStage()
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