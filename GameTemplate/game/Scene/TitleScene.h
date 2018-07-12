#pragma once
#include "myEngine/Graphics/Sprite.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Camera.h"
#include "myEngine/Sound/SoundSource.h"
#include "Map/Map.h"
#include "Player/Player.h"
#include "Camera/GameCamera.h"
#include "TitleBackGround.h"

class TitleScene : public GameObject{
public:
	/*!
	*@brief	コンストラクタ
	*/
	TitleScene();
	/*!
	*@brief	デストラクタ
	*/
	~TitleScene();
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
	*@brief	後から描画
	*/
	void PostRender();
	/*!
	*@brief	解放
	*/
	void Release();
	/*!
	*@brief	ステージ作成
	*/
	void StageCreate();
	/*!
	*@brief	シーン切り替えフラグを取得
	*/
	bool GetChangeSceneFlag() const
	{
		return m_changeScene;
	}
private:
	enum State {
		Entity,		//実体
		Clear		//透明
	};

	State								m_state = Entity;		//状態
	std::unique_ptr<Sprite>				m_pressA;
	TitleBackGround*					m_titleBackGround;		//背景
	CSoundSource*						m_bgmSource;
	bool								m_changeScene = false;	//シーン切り替えフラグ
	float								m_timer = 0.0f;			//タイマー(透明になるまで)
	float								m_alphaTimar = 0.0f;	//タイマー(実体になるまで)
	const float							ALPHA_TIME = 0.5f;		//透明になるまでの時間
};
