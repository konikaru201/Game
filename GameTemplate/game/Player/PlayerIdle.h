/*!
*@brief	�ҋ@�X�e�[�g
*/
#pragma once

#include "IPlayerState.h"

class PlayerIdle : public IPlayerState {
public:
	/*!
	*@brief	�R���X�g���N�^
	* @param[in]	player		�v���C���[
	* @param[in]	psm			�X�e�[�g�}�V��
	*/
	PlayerIdle(Player* player, PlayerStateMachine* psm) :
		IPlayerState(player, psm)
	{
	}
	/*!
	*@brief	�f�X�g���N�^
	*/
	~PlayerIdle()
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
};