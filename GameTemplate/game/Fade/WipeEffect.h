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
	/*!
	*@brief	ワイプの状態
	*/
	enum State {
		WipeIn,		//ワイプイン
		WipeOut		//ワイプアウト
	};

	State		m_state = WipeIn;		//状態
	Sprite*		m_circle;				//円のスプライト
	Sprite*		m_back;					//黒背景のスプライト
	float		m_timer = 0.0f;			//タイマー
	const float WIPE_TIME = 1.0f;		//ワイプする時間
	bool		m_isWipe = false;		//ワイプしているか
};

extern WipeEffect* wipeEffect;