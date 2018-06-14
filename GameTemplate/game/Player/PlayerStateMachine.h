/*!
*@brief	プレイヤーのステートマシン
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "PlayerState.h"
#include "IPlayerState.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerDead.h"
#include "PlayerChangeStage.h"

class PlayerStateMachine : public GameObject {
public:
	/*!
	*@brief	コンストラクタ
	* @param[in]	pl		プレイヤー
	*/
	PlayerStateMachine(Player* pl) :
		m_playerIdle(pl, this),
		m_playerMove(pl, this),
		m_playerDead(pl, this),
		m_playerChangeStage(pl, this)
	{
	}
	/*!
	*@brief	デストラクタ
	*/
	~PlayerStateMachine()
	{
	}
	/*!
	*@brief	更新する前に一度だけ呼ばれる
	*/
	bool Start();
	/*!
	*@brief	更新
	*/
	void Update() {}
	/*!
	*@brief	ステート切り替え
	* @param[in]	nextState		次のステート
	*/
	void ChangeState(PlayerState::PlState nextState);
	/*!
	*@brief	解放
	*/
	void Release();
private:
	PlayerState::PlState m_state = PlayerState::plState_Invald;	//プレイヤーの状態
	IPlayerState* m_currentState = nullptr;						//現在の状態
	PlayerIdle m_playerIdle;									//待機ステート
	PlayerMove m_playerMove;									//移動ステート
	PlayerDead m_playerDead;									//死亡ステート
	PlayerChangeStage m_playerChangeStage;						//スター獲得ステート
};