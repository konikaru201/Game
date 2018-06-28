#include "stdafx.h"
#include "Number.h"

Number::Number()
{
}

Number::~Number()
{
}

void Number::Init(D3DXVECTOR2 numPos, D3DXVECTOR2 numSize)
{
	for (int i = 0; i < 10; i++)
	{
		char filePath[256];
		sprintf(filePath, "Assets/sprite/%d.png", i);
		m_number[i] = std::make_unique<Sprite>();
		m_number[i]->Initialize(filePath);
		m_number[i]->SetSize(numSize);
		m_number[i]->SetPosition(numPos);
	}
}

void Number::NumSet(int n)
{
	m_num = n;
}

void Number::Render()
{
	m_number[m_num]->Render();
}