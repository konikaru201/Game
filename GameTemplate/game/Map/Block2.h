/*!
*@brief	�u���b�N�Q�N���X
*/
#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

class Block2 : public GameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	Block2();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~Block2();
	/*!
	*@brief	������
	* @param[in]	pos		���W
	* @param[in]	rot		��]
	*/
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);
	/*!
	*@brief	�X�V����O�Ɉ�x�����Ă΂��
	*/
	bool Start();
	/*!
	*@brief	�X�V
	*/
	void Update();
	/*!
	*@brief	�`��
	*/
	void Render();
	/*!
	* @brief	���[���h�s����擾
	*@return	���[���h�s��
	*/
	const D3DXMATRIX& GetWorldMatrix() const
	{
		return m_model.GetWorldMatrix();
	}
	/*!
	* @brief	��]�s����擾
	*@return	��]�s��
	*/
	const D3DXMATRIX& GetRotationMatrix() const
	{
		return m_model.GetRotationMatrix();
	}
private:
	SkinModel		m_model;		//�X�L�����f��
	SkinModelData	m_modelData;	//�X�L�����f���f�[�^
	MeshCollider	m_meshCollider;	//���b�V���R���C�_�[
	RigidBody		m_rigidBody;	//����
	Light			m_light;		//���C�g
	D3DXVECTOR3		m_rotationAxis; //��]��
	D3DXVECTOR3		m_position;		//���W
	D3DXQUATERNION	m_rotation;		//��]
};