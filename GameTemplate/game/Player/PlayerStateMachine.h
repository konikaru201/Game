/*!
*@brief	�v���C���[�̃X�e�[�g�}�V��
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "PlayerState.h"
#include "IPlayerState.h"
#include "PlayerIdle.h"
#include "PlayerMove.h"
#include "PlayerDead.h"
#include "PlayerChangeStage.h"

class PlayerStateMachine : public GameObject {
public:
	/*!
	*@brief	�R���X�g���N�^
	* @param[in]	pl		�v���C���[
	*/
	PlayerStateMachine(Player* pl) :
		m_playerIdle(pl, this),
		m_playerMove(pl, this),
		m_playerDead(pl, this),
		m_playerChangeStage(pl, this)
	{
	}
	/*!
	*@brief	�f�X�g���N�^
	*/
	~PlayerStateMachine()
	{
	}
	/*!
	*@brief	�X�V����O�Ɉ�x�����Ă΂��
	*/
	bool Start();
	/*!
	*@brief	�X�V
	*/
	void Update() {}
	/*!
	*@brief	�X�e�[�g�؂�ւ�
	* @param[in]	nextState		���̃X�e�[�g
	*/
	void ChangeState(PlayerState::PlState nextState);
	/*!
	*@brief	���
	*/
	void Release();
private:
	PlayerState::PlState m_state = PlayerState::plState_Invald;	//�v���C���[�̏��
	IPlayerState* m_currentState = nullptr;						//���݂̏��
	PlayerIdle m_playerIdle;									//�ҋ@�X�e�[�g
	PlayerMove m_playerMove;									//�ړ��X�e�[�g
	PlayerDead m_playerDead;									//���S�X�e�[�g
	PlayerChangeStage m_playerChangeStage;						//�X�^�[�l���X�e�[�g
};