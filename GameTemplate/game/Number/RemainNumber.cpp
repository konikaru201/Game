#include "stdafx.h"
#include "RemainNumber.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "Player/Player.h"
#include "Scene/SceneManager.h"

namespace {
	const float NumSizeX = 85.0f;
	const D3DXVECTOR2 NumScale = { 43.0f,54.0f };
}

RemainNumber::RemainNumber()
{
}

RemainNumber::~RemainNumber()
{
	DeleteNum();
}

void RemainNumber::Init(D3DXVECTOR2 position)
{
	m_position = position;
}

bool RemainNumber::Start()
{
	for (int i = 0; i < 2; i++) 
	{
		num[i] = new Number;
	}

	num[0]->Init(m_position + D3DXVECTOR2(NumSizeX, 0.0f), NumScale);
	num[1]->Init(m_position + D3DXVECTOR2(NumSizeX * 2.0f, 0.0f), NumScale);

	num[0]->NumSet(0);
	num[1]->NumSet(m_remainNum);

	return true;
}

void RemainNumber::Update()
{
	if (player != nullptr && sceneManager != nullptr
		&& player->GetPlayerDead() && sceneManager->GetChangeSceneFlag())
	{
		m_remainNum -= 1;
	}

	if (m_remainNum > 99){
		m_remainNum = 99;
	}

	if (m_remainNum < 0)
	{
		m_remainNum = 3;
	}

	num[0]->NumSet(m_remainNum / 10);
	num[1]->NumSet(m_remainNum % 10);
}

void RemainNumber::Render()
{
	for (int i = 0; i < 2; i++)
	{
		num[i]->Render();
	}
}

void RemainNumber::DeleteNum()
{
	for (int i = 0; i < 2; i++)
	{
		delete num[i];
	}
}