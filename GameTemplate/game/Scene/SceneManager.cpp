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
				//g_fade->StartFadeOut();
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
				//�Q�[���V�[�����폜
				gameScene->Release();
				gameScene->SetisDead();
				gameScene = nullptr;
				//�Q�[���I�[�o�[��
				if (g_step == GameScene::step_GameOver) {
					//���U���g�V�[���ɑJ��
					resultScene = goMgr->NewGameObject<ResultScene>();
					state = stateResult;
					f_step = step_WaitFadeIn;
				}
				//�X�e�[�W�N���A��
				else if (g_step == GameScene::step_StageClear) {
					//�X�e�[�W�Z���N�g�V�[���ɑJ��
					stageSelectScene = goMgr->NewGameObject<CStageSelectScene>();
					state = stateStageSelect;
					f_step = step_WaitFadeIn;
				}
			}
		}
		//�ʏ펞
		else if (f_step == step_normal) {
			////�Q�[���V�[���̌��݂̏�Ԃ��擾
			//GameScene::Step g_step = gameScene->IsStep();
			//�Q�[���I�[�o�[���X�e�[�W�N���A�ɂȂ�ƃt�F�[�h�A�E�g
			if (gameScene->GetWaitFadeOut()/*g_step == GameScene::step_GameOver || g_step == GameScene::step_StageClear*/) {
				f_step = step_WaitFadeOut;
				m_changeScene = true;
			}
		}
		break;
	//���U���g�V�[��
	case stateResult:
		//�t�F�[�h�A�E�g��
		if (f_step == step_WaitFadeOut) {
			//�t�F�[�h���I��
			if (!g_fade->IsExecute()) {
				//���U���g�V�[�����폜
				resultScene->SetisDead();
				resultScene = nullptr;
				//�Q�[���V�[���ɑJ��
				gameScene = goMgr->NewGameObject<GameScene>();
				state = stateGame;
				f_step = step_WaitFadeIn;
			}
		}
		//�ʏ펞
		else if(f_step == step_normal){
			//�V�[���؂�ւ����t�F�[�h�A�E�g
			if (resultScene->GetChangeSceneFlag()) {
				g_fade->StartFadeOut();
				f_step = step_WaitFadeOut;
			}
		}
		break;
	}
}
