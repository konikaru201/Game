#pragma once
#include "myEngine/Graphics/Sprite.h"
#include "myEngine/GameObject/GameObject.h"

class ResultScene : public GameObject {
public:
	//�R���X�g���N�^
	ResultScene();

	//�f�X�g���N�^
	~ResultScene();

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
	float alpha = 1.0f;			//�����x�B0.0�ō�
	float timer = 0.0f;			//�^�C�}�[
	bool m_changeScene = false; //�V�[���؂�ւ��t���O
};