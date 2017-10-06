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

	//�t�F�[�h�A�E�g����?
	bool IsExecute()
	{
		return m_isExecute;
	}
	//�t�F�[�h�A�E�g�J�n
	void StartFadeOut()
	{
		m_timer = 0.0f;
		m_isExecute = true;
		m_state = FadeOut;
	}
	//�t�F�[�h�C���J�n
	void StartFadeIn()
	{
		if (sprite->GetAlpha() > 0.0f) {
			m_timer = 0.0f;
			m_isExecute = true;
			m_state = FadeIn;
		}
	}
private:
	//�t�F�[�h�̏��
	enum State {
		FadeOut,	//�t�F�[�h�A�E�g
		FadeIn,		//�t�F�[�h�C��
	};
	Sprite* sprite;
	//Texture texture;
	
	const float FADE_TIME = 0.2f;	//�t�F�[�h���鎞��
	State m_state = FadeIn;		//���
	bool m_isExecute = false;	//�t�F�[�h���s����
	float m_timer = 1.0f;		//�^�C�}�[
};

extern Fade* g_fade;