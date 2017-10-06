#pragma once
#include "myEngine/GameObject/GameObject.h"
#include "TitleScene.h"
#include "ResultScene.h"
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
		stateResult,
	};

	enum FadeStep {
		step_WaitFadeIn,
		step_WaitFadeOut,
		step_normal,		//�����Ȃ�
	};

	//���݂̃V�[�����擾
	SceneState GetScene() {
		return state;
	}
private:
	SceneState state;						//���݂̃V�[��
	FadeStep f_step;
	TitleScene* titleScene = nullptr;		//�^�C�g���V�[��
	ResultScene* result = nullptr;
};

extern SceneManager* sceneManager;