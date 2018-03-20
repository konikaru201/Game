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
		//マップ生成
		map = goMgr->NewGameObject<Map>();

		//ステージ作成
		StageCreate();

		//シルエット生成
		depthStencilRender = goMgr->NewGameObject<DepthStencilRender>();
		//プレイヤー生成
		player = goMgr->NewGameObject<Player>();
		//カメラ生成
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
	//ステージ読み込みが終了
	case step_StageLoad:
		g_fade->StartFadeIn();
		step = step_WaitFadeIn;
		break;

	//フェードイン時
	case step_WaitFadeIn:
		//フェードが終了
		if (!g_fade->IsExecute()) {
			step = step_normal;
		}
		break;

	//通常時
	case step_normal:
		if (m_changeStage) {
			g_fade->StartFadeOut();
			step = step_WaitFadeOut;
		}
		break;

	//フェードアウト時
	case step_WaitFadeOut:
		//フェードが終了
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
	//配置されているオブジェクトの数を計算
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
