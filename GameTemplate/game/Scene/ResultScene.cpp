#include "stdafx.h"
#include "ResultScene.h"
#include "myEngine/system.h"
#include "myEngine/HID/Pad.h"
#include "../Fade/Fade.h"
#include "../myEngine/Timer/Timer.h"

ResultScene::ResultScene() {}
ResultScene::~ResultScene()
{
	delete sprite;
}

namespace {
	const D3DXVECTOR2 BackSize = { 1.0f,1.0f };
	const D3DXVECTOR2 BackPos = { FRAME_BUFFER_WIDTH / 2, FRAME_BUFFER_HEIGHT / 2 };
}

void ResultScene::Initialize()
{
	sprite = new Sprite;
	sprite->Initialize("Assets/sprite/GameOver.png");

	g_fade->StartFadeIn();
}

void ResultScene::Update()
{
	if (isDeside) { return; }

	//Œˆ’è
	if (pad->IsTrigger(pad->enButtonA))
	{
		isDeside = true;
	}
}

void ResultScene::Render()
{
	sprite->Draw();
}