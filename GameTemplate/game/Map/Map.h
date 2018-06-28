/*!
*@brief	�}�b�v�N���X
*/
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
#include "Enemy/StoneMonster.h"
#include "Floor.h"
#include "GalaxyBox.h"
#include "Earth.h"
#include "StageMarker.h"
#include "StageMarker2.h"
#include "StageMarker3.h"
#include "Needle.h"
#include "Needle2.h"
#include "Needle3.h"

//�}�b�v�̔z�u���
struct SMapInfo {
	const char* modelName;		//���f���f�[�^
	D3DXVECTOR3 position;		//���W
	D3DXQUATERNION rotation;	//��]
};

class Map : public GameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	Map();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~Map();
	/*!
	*@brief	�X�V����O�Ɉ�x�����Ă΂��֐�
	*/
	bool Start();
	/*!
	*@brief	�X�V
	*/
	void Update();
	/*!
	*@brief	�}�b�v�̐���
	*@param[in] mapLocInfo	�}�b�v�̔z�u���
	*@param[in] numObject	�}�b�v�̃I�u�W�F�N�g��
	*@param[in] stageNumber	�X�e�[�W�ԍ�
	*/
	void Create(SMapInfo* mapLocInfo, int numObject);
	/*!
	*@brief	�`��
	*/
	void Render();
	/*!
	*@brief	��ԋ߂��ړ����P�̃��[���h�s����v�Z
	*@param[in]		pos		��r����I�u�W�F�N�g�̍��W
	*@return ��ԋ߂��ړ����P�̃��[���h�s��
	*/
	const D3DXMATRIX& GetMoveFloorWorldMatrix(const D3DXVECTOR3& pos);
	/*!
	*@brief	��ԋ߂��ړ����Q�̃��[���h�s����v�Z
	*@param[in]		pos		��r����I�u�W�F�N�g�̍��W
	*@return ��ԋ߂��ړ����Q�̃��[���h�s��
	*/
	const D3DXMATRIX& GetMoveFloor2WorldMatrix(const D3DXVECTOR3& pos);
	/*!
	*@brief	�ړ����P�̃��X�g���擾
	*@return �ړ����P�̃��X�g
	*/
	std::list<MoveFloor*> GetMoveFloorList() const
	{
		return m_moveFloorList;
	}
	/*!
	*@brief	�ړ����Q�̃��X�g���擾
	*@return �ړ����Q�̃��X�g
	*/
	std::list<MoveFloor2*> GetMoveFloor2List() const
	{
		return m_moveFloor2List;
	}
	/*!
	*@brief	��ԋ߂��ړ����P�̍��W���v�Z
	*@param[in]		pos		��r����I�u�W�F�N�g�̍��W
	*@return ��ԋ߂��ړ����P�̍��W
	*/
	const D3DXVECTOR3& GetMoveFloorPosition(const D3DXVECTOR3& pos);
	/*!
	*@brief	��ԋ߂��ړ����P�̍��W���v�Z
	*@param[in]		pos		��r����I�u�W�F�N�g�̍��W
	*@return ��ԋ߂��ړ����P�̍��W
	*/
	const D3DXVECTOR3& GetMoveFloor2Position(const D3DXVECTOR3& pos);
	/*
	*@brief	�n���̃C���X�^���X���擾
	*/
	Earth* GetEarthInstance() const
	{
		return m_earth;
	}
	/*
	*@brief	�X�e�[�W�}�[�J�[�̃C���X�^���X���擾
	*/
	StageMarker* GetStageMarkerInstance() const
	{
		return m_stageMarker;
	}
	/*
	*@brief	�X�e�[�W�}�[�J�[2�̃C���X�^���X���擾
	*/
	StageMarker2* GetStageMarker2Instance() const
	{
		return m_stageMarker2;
	}
	/*
	*@brief	�X�e�[�W�}�[�J�[3�̃C���X�^���X���擾
	*/
	StageMarker3* GetStageMarker3Instance() const
	{
		return m_stageMarker3;
	}
private:
	std::list<MoveFloor*>	m_moveFloorList;	//�ړ����P�̃��X�g
	std::list<MoveFloor2*>	m_moveFloor2List;	//�ړ����Q�̃��X�g
	D3DXMATRIX				moveFloorMatrix;	//�ړ����P�̃��[���h�s��
	D3DXMATRIX				moveFloor2Matrix;	//�ړ����Q�̃��[���h�s��
	Earth*					m_earth;			//�n���̃C���X�^���X
	StageMarker*			m_stageMarker;		//�X�e�[�W�}�[�J�[�̃C���X�^���X
	StageMarker2*			m_stageMarker2;
	StageMarker3*			m_stageMarker3;
};

extern Map* map;
