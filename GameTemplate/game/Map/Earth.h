/*!
*@brief	�n���N���X
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"

class Earth : public GameObject {
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	Earth();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~Earth();
	/*!
	*@brief	������
	* @param[in]	pos		���W
	* @param[in]	rot		��]
	*/
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation);
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
	const D3DXMATRIX& GetWorldMatrix()
	{
		return m_model.GetWorldMatrix();
	}
	/*!
	* @brief	��]���Ă��邩����
	*/
	bool GetIsRotate()
	{
		return m_isRotate;
	}
	/*!
	* @brief	���W�̎擾
	*@return	���W
	*/
	const D3DXVECTOR3& GetPosition() {
		return m_position;
	}
private:
	SkinModel		m_model;			//�X�L�����f��
	SkinModelData	m_modelData;		//�X�L�����f���f�[�^
	MeshCollider	m_meshCollider;		//���b�V���R���C�_�[
	RigidBody		m_rigidBody;		//����
	Light			m_light;			//���C�g
	D3DXVECTOR3		m_position;			//���W
	D3DXQUATERNION	m_rotation;			//��]
	bool			m_isRotate = false;
};
