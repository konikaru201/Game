/*!
*@brief	�X�J�C�{�b�N�X�N���X
*/
#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/GameObject/GameObject.h"

class SkyBox : public GameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	SkyBox();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~SkyBox();
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
private:
	SkinModel		m_model;			//�X�L�����f��
	SkinModelData	m_modelData;		//�X�L�����f���f�[�^
	MeshCollider	m_meshCollider;		//���b�V���R���C�_�[
	D3DXVECTOR3		m_position;			//���W
	D3DXQUATERNION	m_rotation;			//��]
	Light			m_light;			//���C�g
	
	LPDIRECT3DCUBETEXTURE9	m_cubeMapTexture = nullptr;	//�L���[�u�}�b�v�e�N�X�`��
};