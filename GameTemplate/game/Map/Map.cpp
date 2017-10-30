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
		if (strcmp("MoveFloor", mapLocInfo[i].modelName) == 0) {
			//�C���X�^���X�𓮓I�ɐ���
			g_moveFloor = goMgr->NewGameObject<MoveFloor>();
			//���W�Ɖ�]�̏���n���ď�����
			g_moveFloor->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
 		}
		else if (strcmp("MoveFloor2", mapLocInfo[i].modelName) == 0) {
			//�C���X�^���X�𓮓I�ɐ���
			g_moveFloor2 = goMgr->NewGameObject<MoveFloor2>();
			//���W�Ɖ�]�̏���n���ď�����
			g_moveFloor2->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
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
		else if (strcmp("JumpBlock", mapLocInfo[i].modelName) == 0)
		{
			//�C���X�^���X�𓮓I�ɐ���
			jumpBlock = goMgr->NewGameObject<JumpBlock>();
			//���W�Ɖ�]�̏���n���ď�����
			jumpBlock->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("block", mapLocInfo[i].modelName) == 0) 
		{
			//�C���X�^���X�𓮓I�ɐ���
			Block* block = goMgr->NewGameObject<Block>();
			//���W�Ɖ�]�̏���n���ď�����
			block->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("Box", mapLocInfo[i].modelName) == 0) {
			//�C���X�^���X�𓮓I�ɐ���
			Box* box = goMgr->NewGameObject<Box>();
			//���W�Ɖ�]�̏���n���ď�����
			box->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else {
			//MapChip�̃C���X�^���X�𓮓I�ɐ���
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