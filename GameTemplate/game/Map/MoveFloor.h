/*!
*@brief	�ړ����P�N���X
*/
#pragma once

#include "myEngine/Physics/BoxCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

class MoveFloor : public GameObject 
{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	MoveFloor();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~MoveFloor();
	/*!
	*@brief	������
	* @param[in]	pos		���W
	* @param[in]	rot		��]
	*/
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);
	/*!
	*@brief	�X�V����O�Ɉ�x�����Ă΂��֐�
	*/
	bool Start();
	/*!
	*@brief	Update�֐����O�ɌĂ΂��X�V�֐�
	*/
	void PreUpdate();
	/*!
	*@brief	�X�V
	*/
	void Update();
	/*!
	*@brief	�`��
	*/
	void Render();
	/*!
	*@brief	�ړ�
	*/
	void Move();
	/*!
	* @brief	���̍��W�̎擾
	*@return	���̍��W
	*/
	const D3DXVECTOR3& GetPosition()
	{
		return m_position;
	}
	/*!
	* @brief	���̃��[���h�s��̎擾
	*@return	���̃��[���h�s��
	*/
	const D3DXMATRIX& GetWorldMatrix()
	{
		return m_model.GetWorldMatrix();
	}

private:
	SkinModel		m_model;			//�X�L�����f��
	SkinModelData	m_modelData;		//�X�L�����f���f�[�^
	RigidBody		m_rigidBody;		//����
	Light			m_light;			//���C�g
	D3DXVECTOR3		m_position;			//���W
	D3DXQUATERNION	m_rotation;			//��]
	D3DXVECTOR3		m_moveSpeed;		//�ړ����x
	float			m_timer = 0.0f;		//�^�C�}�[
	bool			m_moveFlag = false;	//�ړ��t���O
};