#pragma once
#include "myEngine/Graphics/Sprite.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Camera.h"
#include "myEngine/Sound/SoundSource.h"
#include "Map/Map.h"
#include "Player/Player.h"
#include "Camera/GameCamera.h"
#include "TitleBackGround.h"

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
	*@brief	�ォ��`��
	*/
	void PostRender();
	/*!
	*@brief	���
	*/
	void Release();
	/*!
	*@brief	�X�e�[�W�쐬
	*/
	void StageCreate();
	/*!
	*@brief	�V�[���؂�ւ��t���O���擾
	*/
	bool GetChangeSceneFlag() const
	{
		return m_changeScene;
	}
private:
	enum State {
		Entity,		//����
		Clear		//����
	};

	State								m_state = Entity;		//���
	std::unique_ptr<Sprite>				m_pressA;
	TitleBackGround*					m_titleBackGround;		//�w�i
	CSoundSource*						m_bgmSource;
	bool								m_changeScene = false;	//�V�[���؂�ւ��t���O
	float								m_timer = 0.0f;			//�^�C�}�[(�����ɂȂ�܂�)
	float								m_alphaTimar = 0.0f;	//�^�C�}�[(���̂ɂȂ�܂�)
	const float							ALPHA_TIME = 0.5f;		//�����ɂȂ�܂ł̎���
};
