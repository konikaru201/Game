/*!
*@brief	�^�C�g���w�i�N���X
*/

#pragma once

#include "myEngine/Graphics/Sprite.h"
#include "myEngine/Graphics/Light.h"
#include "myEngine/GameObject/GameObject.h"

class TitleBackGround : public GameObject{
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
	/*!
	*@brief	�[�x�l��`��
	*/
	void RenderDepthValue();
private:
	std::unique_ptr<Sprite> m_backGround;			//�w�i
	SkinModel				m_titleModel;			//3D�^�C�g��
	SkinModelData			m_titleModelData;
	Light					m_light;				//���C�g
	Animation				m_animation;			//�A�j���[�V����
	D3DXQUATERNION			m_rotation;				//��]
	int						m_animationRun = 2;		//����A�j���[�V�����ԍ�
};
