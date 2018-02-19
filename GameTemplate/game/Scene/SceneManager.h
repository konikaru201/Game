#pragma once
#include "myEngine/GameObject/GameObject.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include "StageSelectScene.h"
#include "Scene/GameScene.h"
#include "myEngine/HID/Pad.h"

class SceneManager : public GameObject
{
public:
	//�R���X�g���N�^
	SceneManager();

	//�f�X�g���N�^
	~SceneManager();

	//������
	bool Start();

	//�X�V
	void Update();

	//�V�[���̏��
	enum SceneState {
		stateTitle,
		stateGame,
		stateGameOver,
		stateStageSelect,
	};

	enum FadeStep {
		step_WaitFadeIn,
		step_WaitFadeOut,
		step_normal,		//�����Ȃ�
	};

	//���݂̃V�[�����擾
	const SceneState& GetScene() {
		return state;
	}

	//�V�[���؂�ւ��t���O���擾
	bool GetChangeSceneFlag()
	{
		return m_changeScene;
	}
private:
	SceneState state;								//���݂̃V�[��
	FadeStep f_step;								//�t�F�[�h�̏��
	TitleScene* titleScene = nullptr;				//�^�C�g���V�[��
	CStageSelectScene* stageSelectScene = nullptr;	//�X�e�[�W�Z���N�g�V�[��
	GameScene* gameScene = nullptr;					//�Q�[���V�[��
	bool m_changeScene = false;						//�V�[���؂�ւ��t���O
	int m_gameOverSceneStateNumber = 0;				//�Q�[���I�[�o�[�V�[���̃X�e�[�g�ԍ�
};

extern SceneManager* sceneManager;