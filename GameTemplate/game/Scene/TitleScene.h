#pragma once
#include "myEngine/Graphics/Sprite.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Camera.h"

class TitleScene : public GameObject{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	TitleScene();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~TitleScene();
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
	*@brief	�V�[���؂�ւ��t���O���擾
	*/
	bool GetChangeSceneFlag()
	{
		return m_changeScene;
	}
private:
	Sprite* sprite;					//�X�v���C�g
	Sprite* m_pressA;
	Sprite* m_titleName;
	bool	m_changeScene = false;	//�V�[���؂�ւ��t���O
};
