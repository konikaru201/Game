/*!
*@brief	�ҋ@�X�e�[�g
*/
#pragma once

#include "IStoneMonsterState.h"

class StoneMonsterIdle : public IStoneMonsterState {
public:
	/*!
	*@brief	�R���X�g���N�^
	*@param[in] stoneMonster �X�g�[�������X�^�[
	*@param[in] sms			 �X�e�[�g�}�V��
	*/
	StoneMonsterIdle(StoneMonster* stoneMonster, StoneMonsterStateMachine* sms) :
		IStoneMonsterState(stoneMonster, sms)
	{
	}
	/*!
	*@brief	�f�X�g���N�^
	*/
	~StoneMonsterIdle()
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
	/*!
	*@brief	�ړ�����ł̉�]
	*/
	void TurnOnMoveFloor();
private:
	const float m_speed = 2.0f;							//���x
	D3DXVECTOR3 m_moveSpeed = { 0.0f,0.0f,0.0f };		//�ړ����x
	D3DXVECTOR3 m_destination;							//�ړ���̍��W
	D3DXVECTOR3 m_initPosition;							//�������W
	int			m_rotationFrameCount = 0;				//��]�t���[���J�E���g
	float		m_timer = 0.0f;							//�^�C�}�[
	bool		m_isMove = false;						//�ړ��t���O
	D3DXVECTOR3 m_moveDirection = { 0.0f,0.0f,1.0f };	//�ړ�����
	int			m_turnCount = 0;						//��]�t���[���J�E���g(�ړ�����)
};