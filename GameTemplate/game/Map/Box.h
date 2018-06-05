/*!
*@brief	�{�b�N�X�N���X
*/
#pragma once

#include "myEngine/Physics/BoxCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

class Box : public GameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	Box();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~Box();
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
	/*!
	*@brief	Render�֐�����ɌĂ΂��`��֐�
	*/
	void PostRender();
private:
	enum State {
		Entity,		//����
		Clear		//����
	};
	State			m_state = Entity;		//���

	SkinModel		m_model;				//�X�L�����f��
	SkinModelData	m_modelData;			//�X�L�����f���f�[�^
	RigidBody		m_rigidBody;			//����
	Light			m_light;				//���C�g
	D3DXVECTOR3		m_position;				//���W
	D3DXQUATERNION	m_rotation;				//��]
	float			m_timer = 0.0f;			//�^�C�}�[(�����ɂȂ�܂�)
	float			m_alpha = 1.0f;			//�s�����x�B0.0�œ���
	const float		ALPHA_TIME = 0.5f;		//�����ɂȂ�܂ł̎���
	float			m_alphaTimer = 0.0f;	//�^�C�}�[(���̂ɂȂ�܂�)
};