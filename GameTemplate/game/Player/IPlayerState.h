/*!
*@brief	�v���C���[�̃X�e�[�g�̃C���^�[�t�F�[�X
*/

#pragma once

#include "../myEngine/GameObject/GameObject.h"

class Player;
class PlayerStateMachine;

class IPlayerState : public GameObject {
public:
	/*!
	*@brief	�R���X�g���N�^
	* @param[in]	player		�v���C���[
	* @param[in]	psm			�X�e�[�g�}�V��
	*/
	IPlayerState(Player* player, PlayerStateMachine* psm) :
		m_player(player),
		m_psm(psm)
	{
	}
	/*!
	*@brief	�f�X�g���N�^
	*/
	~IPlayerState() {};
	/*!
	*@brief	�X�V
	*/
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
	AnimationNo			m_currentAnim = AnimationStand;	//���݂̃A�j���[�V����
	Player*				m_player = nullptr;				//�v���C���[
	PlayerStateMachine* m_psm = nullptr;				//�X�e�[�g�}�V��
};