#include "stdafx.h"
#include "DisplayCoin.h"
#include "Scene/GameScene.h"
#include "myEngine/GameObject/GameObjectManager.h"


namespace {
	const float NumSizeX = 180.0f;
	const D3DXVECTOR2 NumScale = { 80.0f,100.0f };
}

DisplayCoin::DisplayCoin()
{
	for (int i = 0; i < 2; i++)
	{
		num[i] = new Number;
	}

	D3DXVECTOR2 CoinPos = gameScene->GetCoinPos();
	num[0]->Init(CoinPos + D3DXVECTOR2(NumSizeX, 0.0f), NumScale);
	num[1]->Init(CoinPos + D3DXVECTOR2(NumSizeX * 2.0f, 0.0f), NumScale);
}

DisplayCoin::~DisplayCoin()
{
	DeleteNum();
}

bool DisplayCoin::Start()
{
	return true;
}

void DisplayCoin::Update()
{
	if (gameScene == nullptr) { return; }
	int CoinNum = gameScene->GetPlayer()->GetCoinCount();

	num[0]->NumSet((CoinNum / 10));
	num[1]->NumSet((CoinNum % 10));
}

void DisplayCoin::Render()
{
	for (int i = 0; i < 2; i++)
	{
		num[i]->Render();
	}
}

void DisplayCoin::DeleteNum()
{
	for (int i = 0; i < 2; i++)
	{
		delete num[i];
	}
}