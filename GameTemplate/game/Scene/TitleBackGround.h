/*!
*@brief	�^�C�g���w�i�N���X
*/

#pragma once

#include "myEngine/Graphics/Sprite.h"
#include "myEngine/Graphics/Light.h"
#include "Camera/GameCamera.h"

class TitleBackGround{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	TitleBackGround();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~TitleBackGround();
	/*!
	*@brief	������
	*/
	void Init();
	/*!
	*@brief	�X�V
	*/
	void Update();
	/*!
	*@brief	�`��
	*/
	void Render();
	/*!
	*@brief	���
	*/
	void Release();
private:
	std::unique_ptr<Sprite> m_backGround;			//�w�i
	SkinModel				m_model;				//���j�e�B�����
	SkinModelData			m_modelData;			
	SkinModel				m_titleModel;			//3D�^�C�g��
	SkinModelData			m_titleModelData;
	Light					m_light;				//���C�g
	Animation				m_animation;			//�A�j���[�V����
	D3DXVECTOR3				m_position;				//���j�e�B�������W
	D3DXQUATERNION			m_rotation;				//���j�e�B������]
	D3DXVECTOR3				m_titlePosition;		//�^�C�g�����W
	D3DXQUATERNION			m_titleRotation;		//�^�C�g����]
	int						m_animationRun = 2;		//����A�j���[�V�����ԍ�
};
