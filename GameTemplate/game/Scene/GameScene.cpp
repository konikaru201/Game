#include "stdafx.h"
#include "GameScene.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "../Fade/Fade.h"
#include "../myEngine/Timer/Timer.h"

SMapInfo Stage2[] = {
#include "locationinfo/stage2.h"
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
	if (step == step_WaitFadeOut) {		
		//�}�b�v����
		map = goMgr->NewGameObject<Map>();
		//�X�e�[�W�쐬
		StageCreate();

		depthStencilRender = goMgr->NewGameObject<DepthStencilRender>();	//�V���G�b�g����
		player = goMgr->NewGameObject<Player>();			//�v���C���[����
		gameCamera = goMgr->NewGameObject<GameCamera>();	//�J��������
		
		return false;
	}
	else {
		step = step_WaitFadeIn;
		g_fade->StartFadeIn();
	}

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
			g_fade->StartFadeOut();
			step = step_GameOver;
		}
		//�X�^�[�l����
		else if (player->GetStarAnimationEnd()) {
			g_fade->StartFadeOut();
			step = step_StageClear;
		}
		g_physicsWorld->Update();
		break;
	//�t�F�[�h�A�E�g��
	case step_WaitFadeOut:
		break;
	//�Q�[���I�[�o�[��
	case step_GameOver:
		//�t�F�[�h���I��
		if (!g_fade->IsExecute()) {
			m_waitFadeOut = true;
		}
		break;
	//�X�e�[�W�N���A��
	case step_StageClear:
		//�t�F�[�h���I��
		if (!g_fade->IsExecute()) {
			m_waitFadeOut = true;
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

void GameScene::StageCreate()
{
	int numObject = sizeof(Stage2) / sizeof(Stage2[0]);

	map->Create(Stage2, numObject);

	bgmSource = goMgr->NewGameObject<CSoundSource>();
	bgmSource->InitStreaming("Assets/sound/bgm_2.wav");
	bgmSource->Play(true);

	step = step_StageLoad;
}

void GameScene::Release()
{
	player->SetisDead();
	player = nullptr;
	depthStencilRender->SetisDead();
	depthStencilRender = nullptr;
	gameCamera->SetisDead();
	gameCamera = nullptr;
	map->SetisDead();
	map = nullptr;
	bgmSource->SetisDead();
	bgmSource = nullptr;
}
