#include "stdafx.h"
#include "SceneManager.h"
#include "Scene/GameScene.h"
#include "myEngine/Physics/Physics.h"
#include "../Fade/Fade.h"
#include "myEngine/GameObject/GameObjectManager.h"

SceneManager::SceneManager()
{
	//�^�C�g����ʐ���
	titleScene = goMgr->NewGameObject<TitleScene>();

	state = stateTitle;
	f_step = step_normal;

	titleScene->Initialize();
}

SceneManager::~SceneManager()
{
	delete titleScene;
	titleScene = nullptr;
	delete result;
	result = nullptr;
	delete gameScene;
	gameScene = nullptr;
}

bool SceneManager::Start()
{
	return true;
}

void SceneManager::Update()
{
	//�t�F�[�h�C����
	if (f_step == step_WaitFadeIn)
	{
		//�t�F�[�h���I��
		if (!g_fade->IsExecute())
		{
			f_step = step_normal;
		}
	}

	switch (state)
	{
	//�^�C�g����ʂ̂Ƃ�
	case stateTitle:
		if (f_step == step_WaitFadeOut) {
			//�t�F�[�h���I��
			if (!g_fade->IsExecute()) {
				//�^�C�g���V�[�����폜
				titleScene->SetisDead();
				titleScene = nullptr;
				//�Q�[���V�[���ɑJ��
				gameScene = new GameScene;
				gameScene->Start();
				state = stateGame;

				f_step = step_WaitFadeIn;
			}
		}
		else if (f_step == step_normal) {
			//���肵��
			if (titleScene->GetisDeside()) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
		}

		break;
	//�Q�[���V�[���̂Ƃ�
	case stateGame:
		//�t�F�[�h�A�E�g��
		if (f_step == step_WaitFadeOut) {
			//�t�F�[�h���I��
			if (!g_fade->IsExecute()) {
				if (gameScene->IsStep() == GameScene::step_GameOver) {
					//���U���g�ɑJ��
					result = goMgr->NewGameObject<ResultScene>();
					result->Initialize();
					state = stateResult;
				}
				
				gameScene->Release();
				gameScene = nullptr;
				f_step = step_WaitFadeIn;
			}
		}
		//�ʏ펞
		else if (f_step == step_normal) {
			GameScene::Step g_step = gameScene->IsStep();
			if (g_step == GameScene::step_GameClear || g_step == GameScene::step_GameOver) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
			gameScene->Update();
		}
		break;
		//�Q�[���I�[�o�[�̂Ƃ�
	case stateResult:
		//�t�F�[�h�A�E�g��
		if (f_step == step_WaitFadeOut) {
			//�t�F�[�h���I��
			if (!g_fade->IsExecute()) {
				result->SetisDead();
				result = nullptr;
				f_step = step_WaitFadeIn;
				//�^�C�g���ɑJ��
				titleScene = goMgr->NewGameObject<TitleScene>();
				titleScene->Initialize();
				state = stateTitle;
			}
		}
		else if(f_step == step_normal){
			if (pad->IsTrigger(pad->enButtonA)) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
		}
		break;
	}
}