/*!
*@brief	フェードクラス
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Sprite.h"
#include "myEngine/Graphics/Texture.h"


class Fade : public GameObject {
public:
	/*!
	*@brief	コンストラクタ
	*/
	Fade();
	/*!
	*@brief	デストラクタ
	*/
	~Fade();
	/*!
	*@brief	更新する前に一度だけ呼ばれる
	*/
	bool Start();
	/*!
	*@brief	更新
	*/
	void Update();
	/*!
	*@brief	描画
	*/
	void Render();
	/*!
	*@brief	フェードアウト中か?
	*/
	bool IsExecute()
	{
		return m_isExecute;
	}
	/*!
	*@brief	フェードアウト開始
	*/
	void StartFadeOut()
	{
		m_timer = 0.0f;
		m_isExecute = true;
		m_state = FadeOut;
	}
	/*!
	*@brief	フェードイン開始
	*/
	void StartFadeIn()
	{
		if (m_sprite->GetAlpha() > 0.0f) {
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
	Sprite*		m_sprite;				//ロード中のスプライト
	
	const float FADE_TIME = 0.2f;		//フェードする時間
	State		m_state = FadeIn;		//状態
	bool		m_isExecute = false;	//フェード実行中か
	float		m_timer = 1.0f;			//タイマー
};

extern Fade* g_fade;