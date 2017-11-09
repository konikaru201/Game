#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "MapChip.h"
#include "MoveFloor.h"
#include "MoveFloor2.h"
#include "Coin.h"
#include "Enemy/Killer.h"
#include "JumpBlock.h"
#include "Block.h"
#include "Box.h"
#include "Test.h"

//�}�b�v�̔z�u���
struct SMapInfo {
	const char* modelName;		//���f���f�[�^
	D3DXVECTOR3 position;		//���W
	D3DXQUATERNION rotation;	//��]
};

class Map : public GameObject
{
public:
	//�R���X�g���N�^
	Map();

	//�f�X�g���N�^
	~Map();

	//������
	bool Start();

	//�X�V
	void Update();

	//�}�b�v�̐���
	//mapLocInfo	�}�b�v�̔z�u���
	//numObject		�}�b�v�̃I�u�W�F�N�g��
	void Create(SMapInfo* mapLocInfo, int numObject);

	//�`��
	void Render();

	////�ړ���(��)�̃C���X�^���X���擾
	//MoveFloor* GetMoveFloor()
	//{
	//	return moveFloor;
	//}

	////�ړ���(�c)�̃C���X�^���X���擾
	//MoveFloor2* GetMoveFloor2()
	//{
	//	return moveFloor2;
	//}

	//�W�����v�u���b�N�̃C���X�^���X���擾
	JumpBlock* GetJumpBlock()
	{
		return jumpBlock;
	}
private:
	//MoveFloor* moveFloor;		//�ړ���(��)�̃C���X�^���X
	//MoveFloor2* moveFloor2;		//�ړ���(�c)�̃C���X�^���X
	JumpBlock* jumpBlock;		//�W�����v�u���b�N�̃C���X�^���X
};

