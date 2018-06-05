/*!
*@brief	���N���X
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Physics/BoxCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Graphics/Light.h"

class Floor : public GameObject{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	Floor();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~Floor();
	/*!
	*@brief	������
	* @param[in]	pos		���W
	* @param[in]	rot		��]
	*/
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);
	/*!
	*@brief	�X�V
	*/
	void Update();
	/*!
	*@brief	�`��
	*/
	void Render();

private:
	SkinModel		m_model;		//�X�L�����f��
	SkinModelData	m_modelData;	//�X�L�����f���f�[�^
	RigidBody		m_rigidBody;	//����
	Light			m_light;		//���C�g
	D3DXVECTOR3		m_position;		//���W
	D3DXQUATERNION	m_rotation;		//��]
};