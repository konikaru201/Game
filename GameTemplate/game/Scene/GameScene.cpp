#include "stdafx.h"
#include "GameScene.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "Fade/Fade.h"
#include "myEngine/Timer/Timer.h"
#include "Number/RemainNumber.h"

SMapInfo Stage1[] = {
#include "locationinfo/stage2.h"
};

SMapInfo Stage2[] = {
#include "locationinfo/stage3.h"
};

SMapInfo Stage3[] = {
#include "locationinfo/stage4.h"
};

/*!
* @brief	�R���X�g���N�^�B
*/
GameScene::GameScene()
{
}
/*!
* @brief	�f�X�g���N�^�B
*/
GameScene::~GameScene()
{
}
/*!
* @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
*/
bool GameScene::Start()
{
	//�}�b�v����
	map = goMgr->NewGameObject<Map>();
	//�X�e�[�W�쐬
	StageCreate(m_stageNumber);

	silhouette = goMgr->NewGameObject<Silhouette>();	//�V���G�b�g����
	player = goMgr->NewGameObject<Player>();			//�v���C���[����
	gameCamera = goMgr->NewGameObject<GameCamera>();	//�J��������

	return true;
}
/*!
* @brief	�X�V�B
*/
void GameScene::Update()
{
	switch (step){
	//�X�e�[�W�ǂݍ��݂��I��
	case step_StageLoad:
		g_fade->StartFadeIn();
		step = step_WaitFadeIn;
		break;

	//�t�F�[�h�C����
	case step_WaitFadeIn:
		//�t�F�[�h���I��
		if (!g_fade->IsExecute()) {
			step = step_normal;
		}
		break;

	//�ʏ펞
	case step_normal:
		//�v���C���[���S��
		if (player->GetPlayerDead()) {
			bgmSource->SetisDead();
			bgmSource = nullptr;
			if (remainNumber->GetRemainNum() <= 0) {
				gameOverScene = goMgr->NewGameObject<GameOverScene>();
				m_restart = false;
			}
			step = step_GameOver;
		}
		//�X�^�[�l����
		else if (player->GetStarAnimationEnd()) {
			bgmSource->SetisDead();
			bgmSource = nullptr;
			g_fade->StartFadeOut();
			step = step_StageClear;
		}
		g_physicsWorld->Update();
		break;
	//�Q�[���I�[�o�[��
	case step_GameOver:
		//�c�@�����O�łȂ��Ȃ烊�X�^�[�g
		if (m_restart) {
			g_fade->StartFadeOut();
			m_gameOverSceneEnd = true;
			m_restart = false;
		}
		//�Q�[���I�[�o�[�V�[�����I��
		else if (gameOverScene != nullptr && gameOverScene->GetGameOverSceneEnd()) {
			m_gameOverSceneStateNumber = gameOverScene->GetStateNumber();
			g_fade->StartFadeOut();
			m_gameOverSceneEnd = true;
			gameOverScene->SetisDead();
			gameOverScene = nullptr;
		}
		g_physicsWorld->Update();
		break;
	//�X�e�[�W�N���A��
	case step_StageClear:
		//�t�F�[�h���I��
		if (!g_fade->IsExecute()) {
			m_stageClearFlag = true;
		}
		break;
	}
}
/*!
* @brief	�`��B
*/
void GameScene::Render()
{
}

void GameScene::StageCreate(int number)
{
	//�X�e�[�W�P
	if(number == 1)
	{
		int numObject = sizeof(Stage1) / sizeof(Stage1[0]);

		map->Create(Stage1, numObject);

		bgmSource = goMgr->NewGameObject<CSoundSource>();
		bgmSource->InitStreaming("Assets/sound/bgm_2.wav");
		bgmSource->Play(true);
	}
	//�X�e�[�W�Q
	else if (number == 2) {
		int numObject = sizeof(Stage2) / sizeof(Stage2[0]);

		map->Create(Stage2, numObject);

		bgmSource = goMgr->NewGameObject<CSoundSource>();
		bgmSource->InitStreaming("Assets/sound/bgm_2.wav");
		bgmSource->Play(true);
	}
	//�X�e�[�W�R
	else if (number == 3) {
		int numObject = sizeof(Stage3) / sizeof(Stage3[0]);

		map->Create(Stage3, numObject);

		bgmSource = goMgr->NewGameObject<CSoundSource>();
		bgmSource->InitStreaming("Assets/sound/bgm_2.wav");
		bgmSource->Play(true);
	}

	step = step_StageLoad;
}

void GameScene::Release()
{
	player->SetisDead();
	player = nullptr;
	silhouette->SetisDead();
	silhouette = nullptr;
	gameCamera->SetisDead();
	gameCamera = nullptr;
	map->SetisDead();
	map = nullptr;
}

void GameScene::SetStageNumber(int number)
{
	m_stageNumber = number;
}
