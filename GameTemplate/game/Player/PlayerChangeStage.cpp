#include "stdafx.h"
#include "PlayerChangeStage.h"
#include "Player.h"
#include "Scene/SceneManager.h"
#include "myEngine/Sound/SoundSource.h"
#include "myEngine/GameObject/GameObjectManager.h"

void PlayerChangeStage::Update()
{
	if (m_animationEnd) {
		return;
	}

	D3DXVECTOR3 moveSpeed = m_player->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	//�v���C���[�̈ړ����x��ݒ�
	m_player->SetMoveSpeed(moveSpeed);

	if (m_player->GetIsOnGround()) {
		//�X�^�[�l�����̃A�j���[�V������ݒ�
		m_currentAnim = AnimationPose;
		m_player->SetCurrentAnim(m_currentAnim);

		if (!m_player->GetAnimationIsPlay()) {
			m_animationEnd = true;
			m_player->SetAnimationEnd(m_animationEnd);
		}
	}
}

bool PlayerChangeStage::Start()
{
	if (m_player->GetSceneSelectFlag()) {
		CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
		SE->Init("Assets/sound/U_Voice_4.wav");
		SE->Play(false);
	}
	else {
		CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
		SE->Init("Assets/sound/U_Voice_3.wav");
		SE->Play(false);
	}

	return true;
}