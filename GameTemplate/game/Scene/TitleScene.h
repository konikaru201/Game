#pragma once
#include "myEngine/Graphics/Sprite.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Camera.h"

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
	*@brief	シーン切り替えフラグを取得
	*/
	bool GetChangeSceneFlag()
	{
		return m_changeScene;
	}
private:
	Sprite* sprite;					//スプライト
	Sprite* m_pressA;
	Sprite* m_titleName;
	bool	m_changeScene = false;	//シーン切り替えフラグ
};
