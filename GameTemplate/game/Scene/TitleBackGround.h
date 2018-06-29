/*!
*@brief	タイトル背景クラス
*/

#pragma once

#include "myEngine/Graphics/Sprite.h"
#include "myEngine/Graphics/Light.h"
#include "Camera/GameCamera.h"

class TitleBackGround{
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
private:
	std::unique_ptr<Sprite> m_backGround;			//背景
	SkinModel				m_model;				//ユニティちゃん
	SkinModelData			m_modelData;			
	SkinModel				m_titleModel;			//3Dタイトル
	SkinModelData			m_titleModelData;
	Light					m_light;				//ライト
	Animation				m_animation;			//アニメーション
	D3DXVECTOR3				m_position;				//ユニティちゃん座標
	D3DXQUATERNION			m_rotation;				//ユニティちゃん回転
	D3DXVECTOR3				m_titlePosition;		//タイトル座標
	D3DXQUATERNION			m_titleRotation;		//タイトル回転
	int						m_animationRun = 2;		//走りアニメーション番号
};
