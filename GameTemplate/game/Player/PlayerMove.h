#pragma once

#include "IPlayerState.h"
#include "myEngine/HID/Pad.h"
#include "Camera/GameCamera.h"

class PlayerMove : public IPlayerState {
public:
	//�R���X�g���N�^
	PlayerMove(Player* player, PlayerStateMachine* psm) :
		IPlayerState(player, psm)
	{
	}

	//�f�X�g���N�^
	~PlayerMove()
	{
	}

	//�X�V
	void Update();

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start();

	//�ړ�����
	//�߂�l�@�ړ����x
	D3DXVECTOR3 Move();

	D3DXVECTOR3 Jump(const D3DXVECTOR3& speed);

	//��]
	void Turn();

private:
	float acceleration = 0.0f;						//�����x
	const float speedLimit = 6.0f;					//���E���x
	D3DXVECTOR3 dir = { 0.0f,0.0f,0.0f };			//����
	D3DXVECTOR3 currentDir = { 0.0f,0.0f,0.0f };	//1�t���[���O��Z����
	int m_rotationFrameCount = 0;					//��]�t���[���J�E���g
	float timer = 0.0f;								//�^�C�}�[
};