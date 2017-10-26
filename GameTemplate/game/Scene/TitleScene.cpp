#include "stdafx.h"
#include "TitleScene.h"
#include "myEngine/system.h"
#include "myEngine/HID/Pad.h"
#include "../Fade/Fade.h"
#include "../myEngine/Timer/Timer.h"

TitleScene::TitleScene(){}
TitleScene::~TitleScene()
{
	delete sprite;
}

namespace {
	const D3DXVECTOR2 BackSize = { 1.0f,1.0f };
	const D3DXVECTOR2 BackPos = { FRAME_BUFFER_WIDTH / 2, FRAME_BUFFER_HEIGHT / 2 };
}

void TitleScene::Initialize()
{
	sprite = new Sprite;
	sprite->Initialize("Assets/sprite/Title.png");

	g_fade->StartFadeIn();
}

void TitleScene::Update()
{
	if (isDeside) { return; }

	//timer += Timer::GetFrameDeltaTime();
	//if (timer >= 2.6f) {
	//	timer = 0.0f;
	//	alpha = 1.0f;
	//}
	//if (timer >= 1.5f && timer < 2.0f) {
	//	alpha -= 0.06f;
	//}
	//else if (timer >= 2.0f && timer < 2.5f) {
	//	alpha += 0.06f;
	//}

	//Œˆ’è
	if (pad->IsTrigger(pad->enButtonA))
	{
		isDeside = true;
	}
}

void TitleScene::Render()
{
	//sprite->SetAlpha(alpha);
	sprite->Draw();
}