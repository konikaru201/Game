/*!
*@brief	�}�b�v�`�b�v�N���X
*/
#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"

class MapChip : public GameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	MapChip();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~MapChip();
	/*!
	*@brief	������
	* @param[in]	modelName		���f���l�[��
	* @param[in]	position		���W
	* @param[in]	rotation		��]
	*/
	void Init(const char* modelName, D3DXVECTOR3 position, D3DXQUATERNION rotation);
	/*!
	*@brief	�X�V
	*/
	void Update();
	/*!
	*@brief	�`��
	*/
	void Render();
private:
	SkinModel		m_model;			//�X�L�����f��
	SkinModelData	m_modelData;		//�X�L�����f���f�[�^
	MeshCollider	m_meshCollider;		//���b�V���R���C�_�[
	RigidBody		m_rigidBody;		//����
	Light			m_light;			//���C�g
};

