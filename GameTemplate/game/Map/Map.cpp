#include "stdafx.h"
#include "Map.h"
#include "myEngine/GameObject/GameObjectManager.h"

Map::Map()
{
}

Map::~Map()
{
}

bool Map::Start()
{
	return true;
}

void Map::Create(SMapInfo* mapLocInfo, int numObject)
{
	//�I�u�W�F�N�g��������[�h���Ă���
	for (int i = 0; i < numObject; i++) {
		if (strcmp("MoveFloor_1", mapLocInfo[i].modelName) == 0) {
			//�C���X�^���X�𓮓I�ɐ���
			MoveFloor* moveFloor = goMgr->NewGameObject<MoveFloor>();
			//���W�Ɖ�]�̏���n���ď�����
			moveFloor->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("MoveFloor_2", mapLocInfo[i].modelName) == 0) {
			//�C���X�^���X�𓮓I�ɐ���
			MoveFloor2* moveFloor2 = goMgr->NewGameObject<MoveFloor2>();
			//���W�Ɖ�]�̏���n���ď�����
			moveFloor2->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("Coin", mapLocInfo[i].modelName) == 0)
		{
			//�C���X�^���X�𓮓I�ɐ���
			Coin* coin = goMgr->NewGameObject<Coin>();
			//���W�Ɖ�]�̏���n���ď�����
			coin->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("Killer", mapLocInfo[i].modelName) == 0)
		{
			//�C���X�^���X�𓮓I�ɐ���
			Killer* killer = goMgr->NewGameObject<Killer>();
			//���W�Ɖ�]�̏���n���ď�����
			killer->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("Spring", mapLocInfo[i].modelName) == 0)
		{
			//�C���X�^���X�𓮓I�ɐ���
			Spring* spring = goMgr->NewGameObject<Spring>();
			//���W�Ɖ�]�̏���n���ď�����
			spring->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("Block_1", mapLocInfo[i].modelName) == 0)
		{
			//�C���X�^���X�𓮓I�ɐ���
			Block* block = goMgr->NewGameObject<Block>();
			//���W�Ɖ�]�̏���n���ď�����
			block->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if(strcmp("Block_2", mapLocInfo[i].modelName) == 0)
		{
			//�C���X�^���X�𓮓I�ɐ���
			Block2* block2 = goMgr->NewGameObject<Block2>();
			//���W�Ɖ�]�̏���n���ď�����
			block2->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("Box", mapLocInfo[i].modelName) == 0) 
		{
			//�C���X�^���X�𓮓I�ɐ���
			Box* box = goMgr->NewGameObject<Box>();
			//���W�Ɖ�]�̏���n���ď�����
			box->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if(strcmp("skyBox", mapLocInfo[i].modelName) == 0)
		{
			//�C���X�^���X�𓮓I�ɐ���
			SkyBox* skyBox = goMgr->NewGameObject<SkyBox>();
			//���W�Ɖ�]�̏���n���ď�����
			skyBox->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("Star", mapLocInfo[i].modelName) == 0)
		{
			//�C���X�^���X�𓮓I�ɐ���
			Star* star = goMgr->NewGameObject<Star>();
			//���W�Ɖ�]�̏���n���ď�����
			star->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("Red_Dragon", mapLocInfo[i].modelName) == 0) {
			//�C���X�^���X�𓮓I�ɐ���
			Red_Dragon* red_Dragon = goMgr->NewGameObject<Red_Dragon>();
			//���W�Ɖ�]�̏���n���ď�����
			red_Dragon->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else 
		{
			//�C���X�^���X�𓮓I�ɐ���
			MapChip* mapChip = goMgr->NewGameObject<MapChip>();
			//�}�b�v�`�b�v�̏���n���ď�����
			mapChip->Init(mapLocInfo[i].modelName, mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
	}
}

void Map::Update()
{
}

void Map::Render()
{
}