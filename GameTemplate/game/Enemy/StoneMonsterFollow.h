/*!
*@brief	�Ǐ]�X�e�[�g
*/
#pragma once

#include "IStoneMonsterState.h"

class StoneMonsterFollow : public IStoneMonsterState {
public:
	/*!
	*@brief	�R���X�g���N�^
	*@param[in] stoneMonster �X�g�[�������X�^�[
	*@param[in] sms			 �X�e�[�g�}�V��
	*/
	StoneMonsterFollow(StoneMonster* stoneMonster, StoneMonsterStateMachine* sms) :
		IStoneMonsterState(stoneMonster, sms)
	{
	}
	/*!
	*@brief	�f�X�g���N�^
	*/
	~StoneMonsterFollow()
	{
	}
	/*!
	*@brief	�X�V
	*/
	void Update();
	/*!
	*@brief	�ړ�
	*/
	void Move();
	/*!
	*@brief	�T��
	*/
	void Search();
	/*!
	*@brief	��]
	*/
	void Turn();
private:
	const float m_speed = 2.0f;						//���x
	D3DXVECTOR3 m_moveSpeed = { 0.0f,0.0f,0.0f };	//�ړ����x
	int			m_rotationFrameCount = 0;			//��]�t���[���J�E���g
	float		m_timer = 0.0f;						//�^�C�}�[
};