/*!
*@brief	�X�^�[�l���X�e�[�g
*/
#pragma once

#include "IPlayerState.h"

class PlayerGetStar : public IPlayerState {
public:
	/*!
	*@brief	�R���X�g���N�^
	* @param[in]	player		�v���C���[
	* @param[in]	psm			�X�e�[�g�}�V��
	*/
	PlayerGetStar(Player* player, PlayerStateMachine* psm) :
		IPlayerState(player, psm)
	{
	}
	/*!
	*@brief	�f�X�g���N�^
	*/
	~PlayerGetStar()
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