#pragma once
#include "myEngine/Graphics/Sprite.h"
#include "myEngine/GameObject/GameObject.h"

namespace {
	const D3DXVECTOR2 gameOverPos = { 0.0f,  200.0f };
	const D3DXVECTOR2 continuePos = { 0.0f, -200.0f };
	const D3DXVECTOR2 stageSelectReturnPos = { 0.0f, -350.0f };
	const D3DXVECTOR2 titleReturnPos = { 0.0f, -500.0f };
	const D3DXVECTOR2 trianglePos = { -580.0f, -200.0f };
}

class GameOverScene : public GameObject {
public:
	//�R���X�g���N�^
	GameOverScene();

	//�f�X�g���N�^
	~GameOverScene();

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

	//���
	enum State {
		state_Continue, //������
		state_return,	//�X�e�[�W�Z���N�g�V�[���ɖ߂�
		state_End,		//�I��
	};

private:
	//�X�v���C�g
	Sprite* m_gameOver;				//�Q�[���I�[�o�[
	Sprite* m_continue;				//�R���e�B�j���[
	Sprite* m_stageSelectReturn;	//�X�e�[�W�I��������
	Sprite* m_titleReturn;			//�^�C�g���ɖ߂�
	Sprite* m_triangle;				//�O�p

	float alpha = 1.0f;				//�����x�B0.0�ō�
	float timer = 0.0f;				//�^�C�}�[
	bool m_changeScene = false;		//�V�[���؂�ւ��t���O
	State state = state_Continue;	//���
	D3DXVECTOR2 m_preTrianglePos;	//�O�p�̃X�v���C�g���W�ۑ��p�ϐ�
};