#include "stdafx.h"
#include "DisplayCoin.h"
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
	for (int i = 0; i < 2; i++)
	{
		m_num[i] = new Number;
	}

	m_num[0]->Init(m_position + D3DXVECTOR2(NumSizeX, 0.0f), NumScale);
	m_num[1]->Init(m_position + D3DXVECTOR2(NumSizeX * 2.0f, 0.0f), NumScale);

	return true;
}

void DisplayCoin::Update()
{

	if (m_coinNum > 99) {
		sceneManager->GetRemainNumber()->RemainCount(1);
		m_coinNum = 0;
	}

	m_num[0]->NumSet(m_coinNum / 10);
	m_num[1]->NumSet(m_coinNum % 10);

}

void DisplayCoin::Render()
{
	for (int i = 0; i < 2; i++)
	{
		m_num[i]->Render();
	}
}

void DisplayCoin::DeleteNum()
{
	for (int i = 0; i < 2; i++)
	{
		delete m_num[i];
	}
}