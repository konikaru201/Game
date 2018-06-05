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
	m_titleScene = goMgr->NewGameObject<TitleScene>();

	m_state = stateTitle;
	m_step = step_normal;

	return true;
}

void SceneManager::Update()
{
	//�t�F�[�h�C����
	if (m_step == step_WaitFadeIn)
	{
		//�t�F�[�h�C�����I��
		if (!g_fade->IsExecute())
		{
			m_step = step_normal;
		}
	}

	m_changeScene = false;

	switch (m_state)
	{
	//�^�C�g���V�[��
	case stateTitle:
		//�t�F�[�h�A�E�g��
		if (m_step == step_WaitFadeOut) {
			//�t�F�[�h���I��
			if (!g_fade->IsExecute()) {
				//�^�C�g���V�[�����폜
				m_titleScene->SetisDead();
				m_titleScene = nullptr;
				//�X�e�[�W�Z���N�g�V�[���ɑJ��
				m_stageSelectScene = goMgr->NewGameObject<CStageSelectScene>();
				m_state = stateStageSelect;
				m_step = step_WaitFadeIn;
			}
		}
		//�ʏ펞
		else if (m_step == step_normal) {
			//�V�[���؂�ւ����t�F�[�h�A�E�g
			if (m_titleScene->GetChangeSceneFlag()) {
				g_fade->StartFadeOut();
				m_step = step_WaitFadeOut;
			}
		}

		break;
	//�X�e�[�W�Z���N�g�V�[��
	case stateStageSelect:
		//�t�F�[�h�A�E�g��
		if (m_step == step_WaitFadeOut) {
			//�t�F�[�h���I��
			if (!g_fade->IsExecute()) {
				//�X�e�[�W�Z���N�g�V�[�����폜
				m_stageSelectScene->Release();
				m_stageSelectScene->SetisDead();
				m_stageSelectScene = nullptr;
				//�Q�[���V�[���ɑJ��
				m_gameScene = goMgr->NewGameObject<GameScene>();
				m_gameScene->SetStageNumber(m_stageNumber);
				m_state = stateGame;
				
				m_step = step_WaitFadeIn;
			}
		}
		//�ʏ펞
		else if (m_step == step_normal) {
			//�t�F�[�h�A�E�g�҂�
			if (m_stageSelectScene->GetWaitFadeOut()) {
				m_step = step_WaitFadeOut;
				m_changeScene = true;
				m_stageNumber = m_stageSelectScene->GetStageNumber();
			}
		}
		break;
	//�Q�[���V�[��
	case stateGame:
		//�t�F�[�h�A�E�g��
		if (m_step == step_WaitFadeOut) {
			//�t�F�[�h���I��
			if (!g_fade->IsExecute()) {
				//�Q�[���V�[���̌��݂̏�Ԃ��擾
				GameScene::Step g_step = m_gameScene->IsStep();
				//�X�e�[�W�N���A��
				if (g_step == GameScene::step_StageClear) {
					//�X�e�[�W�Z���N�g�V�[���ɑJ��
					m_stageSelectScene = goMgr->NewGameObject<CStageSelectScene>();
					m_state = stateStageSelect;
					m_step = step_WaitFadeIn;
					//�Q�[���V�[�����폜
					m_gameScene->Release();
					m_gameScene->SetisDead();
					m_gameScene = nullptr;
				}
				//�Q�[���I�[�o�[��
				if (g_step == GameScene::step_GameOver) {
					m_changeScene = true;
					m_state = stateGameOver;
					m_step = step_WaitFadeIn;
				}
			}
		}
		//�ʏ펞
		else if (m_step == step_normal) {
			//�X�e�[�W�N���A�ɂȂ���
			if (m_gameScene->GetStageClearFlag()) 
			{
				m_step = step_WaitFadeOut;
				m_changeScene = true;
			}
			//�Q�[���I�[�o�[�ɂȂ���
			if (m_gameScene->GetGameOverEnd()) {
				m_step = step_WaitFadeOut;
			}
		}
		break;
	//�Q�[���I�[�o�[�V�[��
	case stateGameOver:
		//�I�������V�[���̔ԍ����擾
		m_gameOverSceneStateNumber = m_gameScene->GetGameOverSceneStateNumber();
		//�Q�[���V�[�����폜
		m_gameScene->Release();
		m_gameScene->SetisDead();
		m_gameScene = nullptr;
		//�R���e�B�j���[
		if (m_gameOverSceneStateNumber == 0) {
			//�Q�[���V�[������蒼��
			m_gameScene = goMgr->NewGameObject<GameScene>();
			m_gameScene->SetStageNumber(m_stageNumber);
			m_state = stateGame;
		}
		//�X�e�[�W�I���ɖ߂�
		else if (m_gameOverSceneStateNumber == 1) {
			//�X�e�[�W�Z���N�g�V�[���ɑJ��
			m_stageSelectScene = goMgr->NewGameObject<CStageSelectScene>();
			m_state = stateStageSelect;
		}
		//�^�C�g���ɖ߂�
		else {
			//�^�C�g���V�[���ɑJ��
			m_titleScene = goMgr->NewGameObject<TitleScene>();
			m_state = stateTitle;
		}
		
		m_step = step_WaitFadeIn;

		break;
	}
}
