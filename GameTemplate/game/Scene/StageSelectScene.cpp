#include "stdafx.h"
#include "StageSelectScene.h"
#include "Fade/Fade.h"
#include "Fade/WipeEffect.h"

SMapInfo Stage0[] = {
#include "locationinfo/stage1.h"
};

namespace {
	//A�{�^���\���̃T�C�Y
	const D3DXVECTOR2 aBottonSize = { 320.0f,180.0f };
	//�X�e�[�W���̃T�C�Y
	const D3DXVECTOR2 stageNameSize = { 1920.0f,1080.0f };
}

CStageSelectScene::CStageSelectScene()
{
}

CStageSelectScene::~CStageSelectScene()
{
}

bool CStageSelectScene::Start()
{
	//�}�b�v����
	//map = goMgr->NewGameObject<Map>();

	//�X�e�[�W�쐬
	//StageCreate();

	//�V���G�b�g����
	m_silhouette = goMgr->NewGameObject<Silhouette>();
	//�v���C���[����
	//player = goMgr->NewGameObject<Player>();
	//�J��������
	//gameCamera = goMgr->NewGameObject<GameCamera>();

	m_stage1 = std::make_unique<Sprite>();
	m_stage1->Initialize("Assets/sprite/Stage1.png");
	m_stage1->SetSize(stageNameSize);
	m_stage1->SetIsTrans(true);

	m_stage2 = std::make_unique<Sprite>();
	m_stage2->Initialize("Assets/sprite/Stage2.png");
	m_stage2->SetSize(stageNameSize);
	m_stage2->SetIsTrans(true);

	m_stage3 = std::make_unique<Sprite>();
	m_stage3->Initialize("Assets/sprite/Stage3.png");
	m_stage3->SetSize(stageNameSize);
	m_stage3->SetIsTrans(true);

	//A�{�^��
	m_aBotton = std::make_unique<Sprite>();
	m_aBotton->Initialize("Assets/sprite/ABotton.png");
	m_aBotton->SetSize(aBottonSize);
	m_aBotton->SetIsTrans(true);

	m_bgmSource = goMgr->NewGameObject<CSoundSource>();
	m_bgmSource->InitStreaming("Assets/sound/bgm_1.wav");
	m_bgmSource->Play(true);

	m_step = step_WaitFadeIn;

	//if (m_step = step_WaitFadeOut) {
	//	
	//}
	//else {
	//	m_step = step_WaitFadeIn;
	//	g_fade->StartFadeIn();
	//}
	
	return true;
}

void CStageSelectScene::Update()
{
	switch (m_step) {
	//�X�e�[�W�ǂݍ��݂��I��
	case step_StageLoad:
		wipeEffect->StartWipeIn();
		m_step = step_WaitFadeIn;
		break;

	//�t�F�[�h�C����
	case step_WaitFadeIn:
		//���C�v�G�t�F�N�g���I��
		if (!wipeEffect->IsExecute()) {
			m_step = step_normal;
		}
		break;

	//�ʏ펞
	case step_normal:
		if (map->GetStageMarkerInstance()->GetStageChangeFlag()
			|| map->GetStageMarker2Instance()->GetStageChangeFlag()
			|| map->GetStageMarker3Instance()->GetStageChangeFlag()) 
		{
			if (map->GetStageMarkerInstance()->GetStageChangeFlag()) {
				m_stageNumber = map->GetStageMarkerInstance()->GetStageNumber();
			}
			else if (map->GetStageMarker2Instance()->GetStageChangeFlag()) {
				m_stageNumber = map->GetStageMarker2Instance()->GetStageNumber();
			}
			else if (map->GetStageMarker3Instance()->GetStageChangeFlag()) {
				m_stageNumber = map->GetStageMarker3Instance()->GetStageNumber();
			}
			
			wipeEffect->StartWipeOut();
			m_step = step_WaitFadeOut;
		}
		break;

	//�t�F�[�h�A�E�g��
	case step_WaitFadeOut:
		//���C�v�G�t�F�N�g���I��
		if (!wipeEffect->IsExecute() && !m_waitFadeOut) {
			m_waitFadeOut = true;
			m_bgmSource->SetisDead();
			m_bgmSource = nullptr;
		}
		break;
	}

	g_physicsWorld->Update();
}

void CStageSelectScene::Render()
{
}

void CStageSelectScene::PostRender()
{
	if (!map->GetStageMarkerInstance()->GetDecisionFlag()
		&& !map->GetStageMarker2Instance()->GetDecisionFlag()
		&& !map->GetStageMarker3Instance()->GetDecisionFlag())
	{
		g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		D3DXVECTOR3 playerPos = player->GetPosition();
		playerPos.y += 2.0f;
		m_aBotton->SetPosition3D(playerPos);
		if (map->GetStageMarkerInstance()->GetUIRenderFlag()) {
			m_aBotton->Render();
			D3DXVECTOR3 markerFromCamera = gameCamera->GetPosition() - map->GetStageMarkerInstance()->GetPosition();
			D3DXVec3Normalize(&markerFromCamera, &markerFromCamera);
			markerFromCamera.z *= 2.0f;
			D3DXVECTOR3 stageNumberPos = map->GetStageMarkerInstance()->GetPosition() + markerFromCamera;
			m_stage1->SetPosition3D(stageNumberPos);
			m_stage1->Render();
		}
		else if (map->GetStageMarker2Instance()->GetUIRenderFlag()) {
			m_aBotton->Render();
			D3DXVECTOR3 markerFromCamera = gameCamera->GetPosition() - map->GetStageMarker2Instance()->GetPosition();
			D3DXVec3Normalize(&markerFromCamera, &markerFromCamera);
			markerFromCamera.z *= 2.0f;
			D3DXVECTOR3 stageNumberPos = map->GetStageMarker2Instance()->GetPosition() + markerFromCamera;
			m_stage2->SetPosition3D(stageNumberPos);
			m_stage2->Render();
		}
		else if (map->GetStageMarker3Instance()->GetUIRenderFlag()) {
			m_aBotton->Render();
			D3DXVECTOR3 markerFromCamera = gameCamera->GetPosition() - map->GetStageMarker3Instance()->GetPosition();
			D3DXVec3Normalize(&markerFromCamera, &markerFromCamera);
			markerFromCamera.z *= 2.0f;
			D3DXVECTOR3 stageNumberPos = map->GetStageMarker3Instance()->GetPosition() + markerFromCamera;
			m_stage3->SetPosition3D(stageNumberPos);
			m_stage3->Render();
		}

		g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

		g_pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	}
}

void CStageSelectScene::StageCreate()
{
	//�}�b�v����
	map = goMgr->NewGameObject<Map>();

	//�z�u����Ă���I�u�W�F�N�g�̐����v�Z
	int numObject = sizeof(Stage0) / sizeof(Stage0[0]);
	map->Create(Stage0, numObject);

	//�J��������
	gameCamera = goMgr->NewGameObject<GameCamera>();

	//�v���C���[����
	player = goMgr->NewGameObject<Player>();

	wipeEffect->StartWipeIn();
	m_step = step_WaitFadeIn;
}

void CStageSelectScene::Release()
{
	map->SetisDead();
	map = nullptr;
	m_silhouette->SetisDead();
	m_silhouette = nullptr;
	player->SetisDead();
	player = nullptr;
	gameCamera->SetisDead();
	gameCamera = nullptr;
}
