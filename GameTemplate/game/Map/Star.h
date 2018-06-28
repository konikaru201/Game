#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

class Star : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	Star();
	/*!
	*@brief	デストラクタ
	*/
	~Star();
	/*!
	*@brief	初期化
	* @param[in]	pos		座標
	* @param[in]	rot		回転
	*/
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);
	/*!
	*@brief	更新
	*/
	void Update();
	/*!
	*@brief	描画
	*/
	void Render();
	/*!
	* @brief	影を描画
	* @param[in]	viewMatrix		ビュー行列
	* @param[in]	projMatrix		プロジェクション行列
	* @param[in]	isDrawShadowMap	シャドウマップを描くフラグ
	* @param[in]	isRecieveShadow	シャドウレシーバーかどうか
	*/
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);
	/*!
	* @brief	プレイヤーの座標の取得
	*@return	プレイヤーの座標
	*/
	const D3DXVECTOR3& GetPosition() const
	{
		return m_position;
	}
	/*!
	*@brief	スター獲得フラグを取得
	*/
	bool GetStar() const
	{
		return m_flag;
	}
private:
	SkinModel		m_model;			//スキンモデル
	SkinModelData	m_modelData;		//スキンモデルデータ
	Light			m_light;			//ライト
	D3DXVECTOR3		m_position;			//座標
	D3DXQUATERNION	m_rotation;			//回転
	D3DXVECTOR3		m_initPosition;		//初期座標
	bool			m_flag = false;		//スター獲得フラグ
	float			m_moveSpeed = 0.05f;//移動速度
	float			m_timer = 0.0f;		//タイマー
};