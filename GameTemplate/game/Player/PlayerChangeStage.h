/*!
*@brief	�X�e�[�W�ύX�X�e�[�g
*/
#pragma once

#include "IPlayerState.h"

class PlayerChangeStage : public IPlayerState {
public:
	/*!
	*@brief	�R���X�g���N�^
	* @param[in]	player		�v���C���[
	* @param[in]	psm			�X�e�[�g�}�V��
	*/
	PlayerChangeStage(Player* player, PlayerStateMachine* psm) :
		IPlayerState(player, psm)
	{
	}
	/*!
	*@brief	�f�X�g���N�^
	*/
	~PlayerChangeStage()
	{
	}
	/*!
	*@brief	�X�V
	*/
	void Update();
	/*!
	*@brief	�X�V����O�Ɉ�x�����Ă΂��
	*/
	bool Start();
private:
	bool m_animationEnd = false;	//�A�j���[�V�����̏I���t���O
};