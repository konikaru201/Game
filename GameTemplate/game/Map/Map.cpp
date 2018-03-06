#include "stdafx.h"
#include "Map.h"
#include "myEngine/GameObject/GameObjectManager.h"

Map* map = nullptr;

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
			m_moveFloorList.push_back(moveFloor);
		}
		else if (strcmp("MoveFloor_2", mapLocInfo[i].modelName) == 0) {
			//�C���X�^���X�𓮓I�ɐ���
			MoveFloor2* moveFloor2 = goMgr->NewGameObject<MoveFloor2>();
			//���W�Ɖ�]�̏���n���ď�����
			moveFloor2->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
			m_moveFloor2List.push_back(moveFloor2);
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
		else if (strcmp("StoneMonster", mapLocInfo[i].modelName) == 0) {
			StoneMonster* stoneMonster = goMgr->NewGameObject<StoneMonster>();
			stoneMonster->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
		}
		else if (strcmp("MoveFloor_3", mapLocInfo[i].modelName) == 0) {
			Floor* floor = goMgr->NewGameObject<Floor>();
			floor->Init(mapLocInfo[i].position, mapLocInfo[i].rotation);
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

const D3DXMATRIX& Map::MoveFloorWorldMatrix(const D3DXVECTOR3& pos)
{
	D3DXMATRIX matrix;
	float minLength = 1000.0f;
	for (auto moveFloor : m_moveFloorList) {
		D3DXVECTOR3 moveFloorPosition = moveFloor->GetPosition();
		D3DXVECTOR3 Vector = pos - moveFloorPosition;
		float length = D3DXVec3Length(&Vector);
		if (minLength > length) {
			matrix = moveFloor->GetWorldMatrix();
			minLength = length;
		}
	}

	return matrix;
}

const D3DXMATRIX & Map::MoveFloor2WorldMatrix(const D3DXVECTOR3 & pos)
{
	D3DXMATRIX matrix;
	float minLength = 1000.0f;
	for (auto moveFloor2 : m_moveFloor2List) {
		D3DXVECTOR3 moveFloorPosition = moveFloor2->GetPosition();
		D3DXVECTOR3 Vector = pos - moveFloorPosition;
		float length = D3DXVec3Length(&Vector);
		if (minLength > length) {
			matrix = moveFloor2->GetWorldMatrix();
			minLength = length;
		}
	}

	return matrix;
}

const D3DXVECTOR3 & Map::GetMoveFloorPosition(const D3DXVECTOR3 & pos)
{
	D3DXVECTOR3 position;
	float minLength = 1000.0f;
	for (auto moveFloor : m_moveFloorList) {
		D3DXVECTOR3 moveFloorPosition = moveFloor->GetPosition();
		D3DXVECTOR3 Vector = pos - moveFloorPosition;
		float length = D3DXVec3Length(&Vector);
		if (minLength > length) {
			position = moveFloorPosition;
			minLength = length;
		}
	}
	return position;
}

const D3DXVECTOR3 & Map::GetMoveFloor2Position(const D3DXVECTOR3 & pos)
{
	D3DXVECTOR3 position;
	float minLength = 1000.0f;
	for (auto moveFloor2 : m_moveFloor2List) {
		D3DXVECTOR3 moveFloorPosition = moveFloor2->GetPosition();
		D3DXVECTOR3 Vector = pos - moveFloorPosition;
		float length = D3DXVec3Length(&Vector);
		if (minLength > length) {
			position = moveFloorPosition;
			minLength = length;
		}
	}
	return position;
}
