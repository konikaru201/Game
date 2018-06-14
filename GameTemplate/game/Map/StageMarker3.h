/*!
*@brief	�X�e�[�W�}�[�J�[�N���X
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"

class StageMarker3 : public GameObject {
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	StageMarker3();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~StageMarker3();
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
	* @brief	�e��`��
	* @param[in]	viewMatrix		�r���[�s��
	* @param[in]	projMatrix		�v���W�F�N�V�����s��
	* @param[in]	isDrawShadowMap	�V���h�E�}�b�v��`���t���O
	* @param[in]	isRecieveShadow	�V���h�E���V�[�o�[���ǂ���
	*/
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);
private:
	SkinModel		m_model;			//�X�L�����f��
	SkinModelData	m_modelData;		//�X�L�����f���f�[�^
	MeshCollider	m_meshCollider;		//���b�V���R���C�_�[
	RigidBody		m_rigidBody;		//����
	Light			m_light;			//���C�g
	D3DXVECTOR3		m_position;			//���W
	D3DXQUATERNION	m_rotation;			//��]
	D3DXMATRIX		m_parentWorldMatrix;
	D3DXVECTOR3		m_childPosition;
	D3DXMATRIX		m_parentRotationMatrix;
	D3DXQUATERNION	m_childRotation;	
	bool			m_stageChange = false;
};
