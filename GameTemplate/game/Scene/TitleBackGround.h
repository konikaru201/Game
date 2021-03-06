/*!
*@brief	タイトル背景クラス
*/

#pragma once

#include "myEngine/Graphics/Sprite.h"
#include "myEngine/Graphics/Light.h"
#include "myEngine/GameObject/GameObject.h"

class TitleBackGround : public GameObject{
public:
	/*!
	*@brief	コンストラクタ
	*/
	TitleBackGround();
	/*!
	*@brief	デストラクタ
	*/
	~TitleBackGround();
	/*!
	*@brief	初期化
	*/
	void Init();
	/*!
	*@brief	更新
	*/
	void Update();
	/*!
	*@brief	描画
	*/
	void Render();
	/*!
	*@brief	解放
	*/
	void Release();
	/*!
	*@brief	深度値を描画
	*/
	void RenderDepthValue();
private:
	std::unique_ptr<Sprite> m_backGround;			//背景
	SkinModel				m_titleModel;			//3Dタイトル
	SkinModelData			m_titleModelData;
	Light					m_light;				//ライト
	Animation				m_animation;			//アニメーション
	D3DXQUATERNION			m_rotation;				//回転
	int						m_animationRun = 2;		//走りアニメーション番号
};
