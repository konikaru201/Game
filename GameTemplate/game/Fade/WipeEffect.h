#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Sprite.h"

class WipeEffect : public GameObject {
public:
	WipeEffect();

	~WipeEffect();

	bool Start();

	void Update();

	void Render();

	void StartWipeOut()
	{
		m_isWipe = true;
		m_timer = 0.0f;
		m_back->SetAlpha(1.0f);
		m_state = WipeOut;
	}

	void StartWipeIn()
	{
		m_isWipe = true;
		m_timer = 0.0f;
		m_back->SetAlpha(1.0f);
		m_state = WipeIn;
	}

	bool IsExecute()
	{
		return m_isWipe;
	}
private:
	enum State {
		WipeIn,
		WipeOut
	};

	State m_state = WipeIn;
	Sprite* m_circle;
	Sprite* m_back;
	float m_timer = 0.0f;
	const float WIPE_TIME = 1.0f;
	bool m_isWipe = false;
};

extern WipeEffect* wipeEffect;