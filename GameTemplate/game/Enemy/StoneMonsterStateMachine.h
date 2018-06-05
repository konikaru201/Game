/*!
*@brief	�X�g�[�������X�^�[�̃X�e�[�g�}�V��
*/
#pragma once

#include "StoneMonsterIdle.h"
#include "StoneMonsterFollow.h"
#include "IStoneMonsterState.h"
#include "myEngine/GameObject/GameObject.h"
#include "StoneMonsterState.h"

class StoneMonsterStateMachine : public GameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^
	* @param[in]	sm		�X�g�[�������X�^�[
	*/
	StoneMonsterStateMachine(StoneMonster* sm) :
		m_stoneMonsterIdle(sm, this),
		m_stoneMonsterFollow(sm, this)
	{
	}
	/*!
	*@brief	�f�X�g���N�^
	*/
	~StoneMonsterStateMachine()
	{
	}
	/*!
	*@brief	�X�V����O�Ɉ�x�����Ă΂��
	*/
	bool Start();
	/*!
	*@brief	�X�V
	*/
	void Update()
	{
	}
	/*!
	*@brief	�X�e�[�g�؂�ւ�
	* @param[in]	nextState		���̃X�e�[�g
	*/
	void ChangeState(StoneMonsterState::EnState nextState);
	/*!
	*@brief	���
	*/
	void Release();
private:
	StoneMonsterState::EnState	m_state = StoneMonsterState::enState_Invald;	//�X�g�[�������X�^�[�̏��
	IStoneMonsterState*			m_currentState = nullptr;						//���݂̏��
	StoneMonsterIdle			m_stoneMonsterIdle;								//�ҋ@�X�e�[�g
	StoneMonsterFollow			m_stoneMonsterFollow;							//�Ǐ]�X�e�[�g
};