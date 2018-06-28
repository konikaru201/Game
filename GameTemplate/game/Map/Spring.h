/*!
*@brief	�o�l�N���X
*/
#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

class Spring : public GameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	Spring();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~Spring();
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
	*@brief	�v���C���[�Ƃ̓����蔻��
	*/
	void CollisionDetection();
	/*!
	* @brief	�ړ����x���擾
	*@return	�ړ����x
	*/
	const D3DXVECTOR3& GetMoveSpeed() const
	{
		return m_jumpSpeed;
	}

private:
	SkinModel		m_model;								//�X�L�����f��
	SkinModelData	m_modelData;							//�X�L�����f���f�[�^
	MeshCollider	m_meshCollider;							//���b�V���R���C�_�[
	RigidBody		m_rigidBody;							//����
	Light			m_light;								//���C�g
	D3DXVECTOR3		m_position;								//���W
	D3DXQUATERNION	m_rotation;								//��]
	D3DXVECTOR3		m_jumpSpeed = { 0.0f, 20.0f, 0.0f };	//�W�����v���x

	D3DXMATRIX		m_parentWorldMatrix;						//�ړ����Q�̃��[���h�s��
	D3DXVECTOR3		m_childPosition = { 0.0f,0.0f,0.0f };		//�ړ����Q�̃��[�J�����W����݂����W
	bool			m_moveFloor2Find = false;					//�ړ����Q�𔭌�������
	D3DXVECTOR3		m_moveFloor2Position = { 0.0f,0.0f,0.0f };	//�ړ����Q�̍��W
};