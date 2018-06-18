#include "stdafx.h"
#include "SceneManager.h"
#include "myEngine/Physics/Physics.h"
#include "Fade/Fade.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "Fade/WipeEffect.h"

namespace {
	//�R�C���̃X�v���C�g�̃T�C�Y�ƍ��W
	const D3DXVECTOR2 coinSize = { 128.0f,72.0f };
	const D3DXVECTOR2 coinPos = { 920.0f, 600.0f };
	//�c�@�̃X�v���C�g�̃T�C�Y�ƍ��W
	const D3DXVECTOR2 remainSize = { 320.0f,240.0f };
	const D3DXVECTOR2 remainPos = { 900.0f,400.0f };
	//�~�L���̃X�v���C�g�̃T�C�Y�ƍ��W
	const D3DXVECTOR2 kakeruSize = { 320.0f,160.0f };
	const D3DXVECTOR2 kakeruPos = { 1030.0f,600.0f };
	const D3DXVECTOR2 kakeru2Pos = { 1030.0f,400.0f };
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	delete m_coin;
	delete m_coinUI;
	delete m_remain;
	delete m_remainNumber;
	delete m_kakeru;
	delete m_kakeru2;
}

bool SceneManager::Start()
{
	//�^�C�g����ʐ���
	m_titleScene = goMgr->NewGameObject<TitleScene>();

	m_state = stateTitle;
	m_step = step_WaitFadeIn;

	//�X�v���C�g�̏�����
	//�R�C���̊G
	m_coin = new Sprite();
	m_coin->Initialize("Assets/sprite/Coin2.png");
	m_coin->SetPosition(coinPos);
	m_coin->SetSize(coinSize);
	//�R�C���̖���
	m_coinUI = new DisplayCoin();
	m_coinUI->Init(kakeruPos);
	m_coinUI->Start();
	//�c�@
	m_remain = new Sprite;
	m_remain->Initialize("Assets/sprite/unityChan.png");
	m_remain->SetPosition(remainPos);
	m_remain->SetSize(remainSize);
	//�c�@��
	m_remainNumber = new RemainNumber;
	m_remainNumber->Init(kakeru2Pos);
	m_remainNumber->Start();
	//�~�L��
	m_kakeru = new Sprite;
	m_kakeru->Initialize("Assets/sprite/�~.png");
	m_kakeru->SetPosition(kakeruPos);
	m_kakeru->SetSize(kakeruSize);
	m_kakeru2 = new Sprite;
	m_kakeru2->Initialize("Assets/sprite/�~.png");
	m_kakeru2->SetPosition(kakeru2Pos);
	m_kakeru2->SetSize(kakeruSize);


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
				g_fade->StartFadeIn();
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
			if (!wipeEffect->IsExecute()) {
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
		m_coinUI->Update();
		m_remainNumber->Update();

		break;
	//�Q�[���V�[��
	case stateGame:
		//�t�F�[�h�A�E�g��
		if (m_step == step_WaitFadeOut) {
			//�t�F�[�h���I��
			if (!g_fade->IsExecute() && !wipeEffect->IsExecute()) {
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
		m_coinUI->Update();
		m_remainNumber->Update();

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

void SceneManager::PostRender()
{
	if (m_state == stateStageSelect || m_state == stateGame) {
		//�A���t�@�u�����f�B���O��L���ɂ���B
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		//�R�C���̊G�Ɩ�����`��
		m_coin->Render();
		m_coinUI->Render();
		//�c�@�̕`��
		m_remain->Render();
		m_remainNumber->Render();
		//�~�L���̕`��
		m_kakeru->Render();
		m_kakeru2->Render();
		//�A���t�@�u�����f�B���O�𖳌��ɂ���B
		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}
}
