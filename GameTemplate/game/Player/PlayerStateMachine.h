#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "PlayerState.h"
#include "IPlayerState.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerDead.h"
#include "PlayerGetStar.h"

class PlayerStateMachine : public GameObject {
public:
	//コンストラクタ
	PlayerStateMachine(Player* pl) :
		m_playerIdle(pl, this),
		m_playerMove(pl, this),
		m_playerDead(pl, this),
		m_playerGetStar(pl, this)
	{
	}

	//デストラクタ
	~PlayerStateMachine()
	{
	}

	//更新する前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update() {}

	//ステート切り替え
	void ChangeState(PlayerState::PlState nextState);

	//解放
	void Release();

private:
	PlayerState::PlState m_state = PlayerState::plState_Invald;
	IPlayerState* m_currentState = nullptr;
	PlayerIdle m_playerIdle;
	PlayerMove m_playerMove;
	PlayerDead m_playerDead;
	PlayerGetStar m_playerGetStar;
};