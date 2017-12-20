#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "MapChip.h"
#include "MoveFloor.h"
#include "MoveFloor2.h"
#include "Coin.h"
#include "Enemy/Killer.h"
#include "Spring.h"
#include "Block.h"
#include "Block2.h"
#include "Box.h"
#include "SkyBox.h"
#include "Star.h"
#include "Enemy/Red_Dragon.h"

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

	//�W�����v�u���b�N�̃C���X�^���X���擾
	Spring* GetSpring()
	{
		return spring;
	}
private:
	Spring* spring;		//�W�����v�u���b�N�̃C���X�^���X
};

