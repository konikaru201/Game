/*!
*@brief	�����P�N���X
*/
#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"

class Building_a : public GameObject {
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	Building_a();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~Building_a();
	/*!
	*@brief	������
	* @param[in]	pos		���W
	* @param[in]	rot		��]
	*/
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation);
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
	D3DXVECTOR3		m_position;			//���W
	D3DXQUATERNION	m_rotation;			//��]
};