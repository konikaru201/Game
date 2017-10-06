#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Sprite.h"
#include "myEngine/Graphics/Texture.h"

class Fade : public GameObject {
public:
	Fade();
	~Fade();
	bool Start();
	void Update();
	void Render();

	//フェードアウト中か?
	bool IsExecute()
	{
		return m_isExecute;
	}
	//フェードアウト開始
	void StartFadeOut()
	{
		m_timer = 0.0f;
		m_isExecute = true;
		m_state = FadeOut;
	}
	//フェードイン開始
	void StartFadeIn()
	{
		if (sprite->GetAlpha() > 0.0f) {
			m_timer = 0.0f;
			m_isExecute = true;
			m_state = FadeIn;
		}
	}
private:
	//フェードの状態
	enum State {
		FadeOut,	//フェードアウト
		FadeIn,		//フェードイン
	};
	Sprite* sprite;
	//Texture texture;
	
	const float FADE_TIME = 0.2f;	//フェードする時間
	State m_state = FadeIn;		//状態
	bool m_isExecute = false;	//フェード実行中か
	float m_timer = 1.0f;		//タイマー
};

extern Fade* g_fade;