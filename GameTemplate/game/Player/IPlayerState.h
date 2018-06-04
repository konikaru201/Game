#pragma once

#include "../myEngine/GameObject/GameObject.h"

class Player;
class PlayerStateMachine;

class IPlayerState : public GameObject {
public:
	//コンストラクタ
	IPlayerState(Player* player, PlayerStateMachine* psm) :
		m_player(player),
		m_psm(psm)
	{
	}

	//デストラクタ
	~IPlayerState() {};

	virtual void Update() = 0;

	//アニメーションの状態
	enum AnimationNo {
		AnimationStand,	//立ち
		AnimationWalk,	//歩く
		AnimationRun,	//走る
		AnimationJump,	//ジャンプ
		AnimationPose,	//ポーズ
		AnimationDead,	//死亡
	};

protected:
	AnimationNo m_currentAnim = AnimationStand;
	Player* m_player = nullptr;
	PlayerStateMachine* m_psm = nullptr;
};