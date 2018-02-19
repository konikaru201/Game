#include "stdafx.h"
#include "SceneManager.h"
#include "myEngine/Physics/Physics.h"
#include "../Fade/Fade.h"
#include "myEngine/GameObject/GameObjectManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

bool SceneManager::Start()
{
	//�^�C�g����ʐ���
	titleScene = goMgr->NewGameObject<TitleScene>();

	state = stateTitle;
	f_step = step_normal;

	return true;
}

void SceneManager::Update()
{
	//�t�F�[�h�C����
	if (f_step == step_WaitFadeIn)
	{
		//�t�F�[�h�C�����I��
		if (!g_fade->IsExecute())
		{
			f_step = step_normal;
		}
	}

	m_changeScene = false;

	switch (state)
	{
	//�^�C�g���V�[��
	case stateTitle:
		//�t�F�[�h�A�E�g��
		if (f_step == step_WaitFadeOut) {
			//�t�F�[�h���I��
			if (!g_fade->IsExecute()) {
				//�^�C�g���V�[�����폜
				titleScene->SetisDead();
				titleScene = nullptr;
				//�X�e�[�W�Z���N�g�V�[���ɑJ��
				stageSelectScene = goMgr->NewGameObject<CStageSelectScene>();
				state = stateStageSelect;
				f_step = step_WaitFadeIn;
			}
		}
		//�ʏ펞
		else if (f_step == step_normal) {
			//�V�[���؂�ւ����t�F�[�h�A�E�g
			if (titleScene->GetChangeSceneFlag()) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
		}

		break;
	//�X�e�[�W�Z���N�g�V�[��
	case stateStageSelect:
		//�t�F�[�h�A�E�g��
		if (f_step == step_WaitFadeOut) {
			//�t�F�[�h���I��
			if (!g_fade->IsExecute()) {
				//�X�e�[�W�Z���N�g�V�[�����폜
				stageSelectScene->Release();
				stageSelectScene->SetisDead();
				stageSelectScene = nullptr;
				//�Q�[���V�[���ɑJ��
				gameScene = goMgr->NewGameObject<GameScene>();
				state = stateGame;
				f_step = step_WaitFadeIn;
			}
		}
		//�ʏ펞
		else if (f_step == step_normal) {
			//�t�F�[�h�A�E�g�҂�
			if (stageSelectScene->GetWaitFadeOut()) {
				f_step = step_WaitFadeOut;
				m_changeScene = true;
			}
		}
		break;
	//�Q�[���V�[��
	case stateGame:
		//�t�F�[�h�A�E�g��
		if (f_step == step_WaitFadeOut) {
			//�t�F�[�h���I��
			if (!g_fade->IsExecute()) {
				//�Q�[���V�[���̌��݂̏�Ԃ��擾
				GameScene::Step g_step = gameScene->IsStep();
				//�X�e�[�W�N���A��
				if (g_step == GameScene::step_StageClear) {
					//�X�e�[�W�Z���N�g�V�[���ɑJ��
					stageSelectScene = goMgr->NewGameObject<CStageSelectScene>();
					state = stateStageSelect;
					f_step = step_WaitFadeIn;
					//�Q�[���V�[�����폜
					gameScene->Release();
					gameScene->SetisDead();
					gameScene = nullptr;
				}
				//�Q�[���I�[�o�[��
				if (g_step == GameScene::step_GameOver) {
					m_changeScene = true;
					state = stateGameOver;
					f_step = step_WaitFadeIn;
				}
			}
		}
		//�ʏ펞
		else if (f_step == step_normal) {
			//�X�e�[�W�N���A�ɂȂ���
			if (gameScene->GetStageClearFlag()) 
			{
				f_step = step_WaitFadeOut;
				m_changeScene = true;
			}
			//�Q�[���I�[�o�[�ɂȂ���
			if (gameScene->GetGameOverEnd()) {
				f_step = step_WaitFadeOut;
			}
		}
		break;
	//�Q�[���I�[�o�[�V�[��
	case stateGameOver:
		m_gameOverSceneStateNumber = gameScene->GetGameOverSceneStateNumber();
		//�Q�[���V�[�����폜
		gameScene->Release();
		gameScene->SetisDead();
		gameScene = nullptr;
		//�R���e�B�j���[
		if (m_gameOverSceneStateNumber == 0) {
			//�Q�[���V�[������蒼��
			gameScene = goMgr->NewGameObject<GameScene>();
			state = stateGame;
		}
		//�X�e�[�W�I���ɖ߂�
		else if (m_gameOverSceneStateNumber == 1) {
			//�X�e�[�W�Z���N�g�V�[���ɑJ��
			stageSelectScene = goMgr->NewGameObject<CStageSelectScene>();
			state = stateStageSelect;
		}
		//�^�C�g���ɖ߂�
		else {
			//�^�C�g���V�[���ɑJ��
			titleScene = goMgr->NewGameObject<TitleScene>();
			state = stateTitle;
		}
		
		f_step = step_WaitFadeIn;

		break;
	}
}
