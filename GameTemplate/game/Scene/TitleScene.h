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
	bool GetChangeSceneFlag() const
	{
		return m_changeScene;
	}
private:
	std::unique_ptr<Sprite> sprite;					//�X�v���C�g
	std::unique_ptr<Sprite> m_pressA;
	std::unique_ptr<Sprite> m_titleName;
	bool	m_changeScene = false;	//�V�[���؂�ւ��t���O
};
