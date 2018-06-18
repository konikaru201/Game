/*!
*@brief	針クラス
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"

class Needle3 : public GameObject {
public:
	/*!
	*@brief	コンストラクタ
	*/
	Needle3();
	/*!
	*@brief	デストラクタ
	*/
	~Needle3();
	/*!
	*@brief	初期化
	* @param[in]	pos		座標
	* @param[in]	rot		回転
	*/
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation);
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
	* @brief	影を描画
	* @param[in]	viewMatrix		ビュー行列
	* @param[in]	projMatrix		プロジェクション行列
	* @param[in]	isDrawShadowMap	シャドウマップを描くフラグ
	* @param[in]	isRecieveShadow	シャドウレシーバーかどうか
	*/
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);
private:
	SkinModel		m_model;				//スキンモデル
	SkinModelData	m_modelData;			//スキンモデルデータ
	Light			m_light;				//ライト
	D3DXVECTOR3		m_position;				//座標
	D3DXQUATERNION	m_rotation;				//回転
	D3DXMATRIX		m_parentWorldMatrix;	//親のワールド行列
	D3DXVECTOR3		m_childPosition;		//親から見た座標
	D3DXQUATERNION	m_childRotation;		//親から見た回転
	const float		m_moveSpeed = 2.0f;		//速度
	float			m_timer = 0.0f;			//タイマー
	bool			m_upFlag = false;		//上に動くフラグ
};
