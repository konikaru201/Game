#include "stdafx.h"
#include "TitleScene.h"
#include "myEngine/system.h"
#include "myEngine/HID/Pad.h"
#include "Fade/Fade.h"
#include "myEngine/Timer/Timer.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "myEngine/Sound/SoundSource.h"

TitleScene* titleScene;

TitleScene::TitleScene(){}
TitleScene::~TitleScene()
{
	delete sprite;
}

bool TitleScene::Start()
{
	sprite = new Sprite;
	sprite->Initialize("Assets/sprite/Title.png");

	g_fade->StartFadeIn();

	return true;
}

void TitleScene::Update()
{
	//Œˆ’è
	if (pad->IsTrigger(pad->enButtonA))
	{
		CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
		SE->Init("Assets/sound/Desision_2.wav");
		SE->Play(false);
		m_changeScene = true;
	}
}

void TitleScene::Render()
{
	sprite->Render();
}