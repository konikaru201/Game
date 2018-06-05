/*!
*@brief	�ړ��X�e�[�g
*/
#pragma once

#include "IPlayerState.h"
#include "myEngine/HID/Pad.h"
#include "Camera/GameCamera.h"

class PlayerMove : public IPlayerState {
public:
	/*!
	*@brief	�R���X�g���N�^
	* @param[in]	player		�v���C���[
	* @param[in]	psm			�X�e�[�g�}�V��
	*/
	PlayerMove(Player* player, PlayerStateMachine* psm) :
		IPlayerState(player, psm)
	{
	}
	/*!
	*@brief	�f�X�g���N�^
	*/
	~PlayerMove()
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
	*@brief	�ړ����x���v�Z
	*@return �ړ����x
	*/
	D3DXVECTOR3 Move();
	/*!
	*@brief	�W�����v���x���v�Z
	*@return �W�����v���x
	*/
	D3DXVECTOR3 Jump(const D3DXVECTOR3& speed);
	/*!
	*@brief	��]���v�Z
	*/
	void Turn();
private:
	float		m_acceleration = 0.0f;				//�����x
	const float m_speedLimit = 6.0f;				//���E���x
	D3DXVECTOR3 m_dir = { 0.0f,0.0f,0.0f };			//����
	D3DXVECTOR3 m_currentDir = { 0.0f,0.0f,0.0f };	//1�t���[���O��Z����
	int			m_rotationFrameCount = 0;			//��]�t���[���J�E���g
	float		m_timer = 0.0f;						//�^�C�}�[
};