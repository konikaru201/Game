/*!
*@brief	プレイヤーのステートのインターフェース
*/

#pragma once

#include "../myEngine/GameObject/GameObject.h"

class Player;
class PlayerStateMachine;

class IPlayerState : public GameObject {
public:
	/*!
	*@brief	コンストラクタ
	* @param[in]	player		プレイヤー
	* @param[in]	psm			ステートマシン
	*/
	IPlayerState(Player* player, PlayerStateMachine* psm) :
		m_player(player),
		m_psm(psm)
	{
	}
	/*!
	*@brief	デストラクタ
	*/
	~IPlayerState() {};
	/*!
	*@brief	更新
	*/
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
	AnimationNo			m_currentAnim = AnimationStand;	//現在のアニメーション
	Player*				m_player = nullptr;				//プレイヤー
	PlayerStateMachine* m_psm = nullptr;				//ステートマシン
};