#pragma once
#include "myEngine/Graphics/Sprite.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Camera.h"

class TitleScene : public GameObject{
public:
	//�R���X�g���N�^
	TitleScene();

	//�f�X�g���N�^
	~TitleScene();

	//�X�V�����O�Ɉ�x�����Ă΂��֐�
	bool Start();

	//�X�V
	void Update();

	//�`��
	void Render();

	//�V�[���؂�ւ��t���O���擾
	bool GetChangeSceneFlag()
	{
		return m_changeScene;
	}
private:
	Sprite* sprite;				//�X�v���C�g
	float alpha = 1.0f;			//�s�����x�B1.0�͍�
	float timer = 0.0f;			//�^�C�}�[
	bool m_changeScene = false; //�V�[���؂�ւ��t���O
};
