#include "stdafx.h"
#include "StageSelectScene.h"
#include "Fade/Fade.h"

SMapInfo Stage0[] = {
#include "locationinfo/stage1.h"
};

CStageSelectScene::CStageSelectScene()
{
}

CStageSelectScene::~CStageSelectScene()
{
}

bool CStageSelectScene::Start()
{
	if (step = step_WaitFadeOut) {
		//�}�b�v����
		map = goMgr->NewGameObject<Map>();

		//�X�e�[�W�쐬
		StageCreate();

		//�V���G�b�g����
		depthStencilRender = goMgr->NewGameObject<DepthStencilRender>();
		//�v���C���[����
		player = goMgr->NewGameObject<Player>();
		//�J��������
		gameCamera = goMgr->NewGameObject<GameCamera>();
	}
	else {
		step = step_WaitFadeIn;
		g_fade->StartFadeIn();
	}
	
	return true;
}

void CStageSelectScene::Update()
{
	switch (step) {
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
		if (m_changeStage) {
			g_fade->StartFadeOut();
			step = step_WaitFadeOut;
		}
		break;

	//�t�F�[�h�A�E�g��
	case step_WaitFadeOut:
		//�t�F�[�h���I��
		if (!g_fade->IsExecute() && !m_waitFadeOut) {
			m_waitFadeOut = true;
		}
		break;
	}

	g_physicsWorld->Update();
}

void CStageSelectScene::Render()
{
}

void CStageSelectScene::StageCreate()
{
	//�z�u����Ă���I�u�W�F�N�g�̐����v�Z
	int numObject = sizeof(Stage0) / sizeof(Stage0[0]);
	map->Create(Stage0, numObject);

	bgmSource = goMgr->NewGameObject<CSoundSource>();
	bgmSource->InitStreaming("Assets/sound/bgm_1.wav");
	//bgmSource->Init("Assets/sound/bgm_1.wav");
	bgmSource->Play(true);

	step = step_StageLoad;
}

void CStageSelectScene::Release()
{
	map->SetisDead();
	map = nullptr;
	depthStencilRender->SetisDead();
	depthStencilRender = nullptr;
	player->SetisDead();
	player = nullptr;
	gameCamera->SetisDead();
	gameCamera = nullptr;
	bgmSource->SetisDead();
	bgmSource = nullptr;
}
