#include "stdafx.h"
#include "PlayerDead.h"
#include "Player.h"
#include "myEngine/Timer/Timer.h"
#include "myEngine/Sound/SoundSource.h"
#include "myEngine/GameObject/GameObjectManager.h"

void PlayerDead::Update()
{
	if (m_deadTimerFlag) {
		return;
	}

	Dead();
}

bool PlayerDead::Start()
{
	if (m_player->GetHitEnemy()) {
		//死亡アニメーションを設定
		m_currentAnim = AnimationDead;
		m_player->SetCurrentAnim(m_currentAnim);
	}

	CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
	SE->Init("Assets/sound/U_Voice_2.wav");
	SE->Play(false);

	return true;
}

void PlayerDead::Dead()
{
	D3DXVECTOR3 moveSpeed = m_player->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	//プレイヤーの移動速度を設定
	m_player->SetMoveSpeed(moveSpeed);

	m_timer += Timer::GetFrameDeltaTime();
	if (m_timer >= 2.0f) {
		m_deadTimerFlag = true;
		m_player->SetPlayerDead(m_deadTimerFlag);
	}
}
