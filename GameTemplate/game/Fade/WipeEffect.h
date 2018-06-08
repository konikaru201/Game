/*!
*@brief	ワイプエフェクトクラス
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Sprite.h"

class WipeEffect : public GameObject {
public:
	/*!
	*@brief	コンストラクタ
	*/
	WipeEffect();
	/*!
	*@brief	デストラクタ
	*/
	~WipeEffect();
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
	*@brief	ワイプアウト開始
	*/
	void StartWipeOut()
	{
		m_isWipe = true;
		m_timer = 0.0f;
		m_back->SetAlpha(1.0f);
		m_state = WipeOut;
	}
	/*!
	*@brief	ワイプイン開始
	*/
	void StartWipeIn()
	{
		m_isWipe = true;
		m_timer = 0.0f;
		m_back->SetAlpha(1.0f);
		m_state = WipeIn;
	}
	/*!
	*@brief	ワイプ実行中か?
	*/
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