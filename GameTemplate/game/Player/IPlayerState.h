#pragma once

#include "../myEngine/GameObject/GameObject.h"

class Player;
class PlayerStateMachine;

class IPlayerState : public GameObject {
public:
	//�R���X�g���N�^
	IPlayerState(Player* player, PlayerStateMachine* psm) :
		m_player(player),
		m_psm(psm)
	{
	}

	//�f�X�g���N�^
	~IPlayerState() {};

	virtual void Update() = 0;

	//�A�j���[�V�����̏��
	enum AnimationNo {
		AnimationStand,	//����
		AnimationWalk,	//����
		AnimationRun,	//����
		AnimationJump,	//�W�����v
		AnimationPose,	//�|�[�Y
		AnimationDead,	//���S
	};

protected:
	AnimationNo m_currentAnim = AnimationStand;
	Player* m_player = nullptr;
	PlayerStateMachine* m_psm = nullptr;
};