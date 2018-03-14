#include "stdafx.h"
#include "DisplayCoin.h"
//#include "Scene/GameScene.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "Player/Player.h"
#include "Scene/SceneManager.h"

namespace {
	const float NumSizeX = 85.0f;
	const D3DXVECTOR2 NumScale = { 43.0f,54.0f };
}

DisplayCoin::DisplayCoin()
{
}

DisplayCoin::~DisplayCoin()
{
	DeleteNum();
}

void DisplayCoin::Init(D3DXVECTOR2 position)
{
	m_position = position;
}

bool DisplayCoin::Start()
{
	for (int i = 0; i < 3; i++)
	{
		num[i] = new Number;
	}

	num[0]->Init(m_position + D3DXVECTOR2(NumSizeX, 0.0f), NumScale);
	num[1]->Init(m_position + D3DXVECTOR2(NumSizeX * 2.0f, 0.0f), NumScale);
	num[2]->Init(m_position + D3DXVECTOR2(NumSizeX * 3.0f, 0.0f), NumScale);

	return true;
}

void DisplayCoin::Update()
{
	if (player != nullptr && sceneManager != nullptr
		&& player->GetPlayerDead() && sceneManager->GetChangeSceneFlag()) 
	{
		m_coinNum = 0;
	}

	if (m_coinNum > 999) {
		m_coinNum = 999;
	}

	num[0]->NumSet((m_coinNum / 100));
	num[1]->NumSet((m_coinNum / 10) % 10);
	num[2]->NumSet((m_coinNum % 10));
}

void DisplayCoin::Render()
{
	for (int i = 0; i < 3; i++)
	{
		num[i]->Render();
	}
}

void DisplayCoin::DeleteNum()
{
	for (int i = 0; i < 3; i++)
	{
		delete num[i];
	}
}