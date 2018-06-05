/*!
*@brief	���S�X�e�[�g
*/
#pragma once

#include "IPlayerState.h"

class PlayerDead : public IPlayerState{
public:
	/*!
	*@brief	�R���X�g���N�^
	* @param[in]	player		�v���C���[
	* @param[in]	psm			�X�e�[�g�}�V��
	*/
	PlayerDead(Player* player, PlayerStateMachine* psm) :
		IPlayerState(player, psm)
	{
	}
	/*!
	*@brief	�f�X�g���N�^
	*/
	~PlayerDead()
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
	/*!
	*@brief	���S����
	*/
	void Dead();
private:
	float m_timer = 0.0f;			//�^�C�}�[
	bool m_deadTimerFlag = false;	//���S��ɃV�[����؂�ւ��邽�߂̃t���O
};