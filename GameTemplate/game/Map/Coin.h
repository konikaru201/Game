/*!
*@brief	コインクラス
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"

struct CoinInfo {
	D3DXVECTOR3 position;		//座標
	D3DXQUATERNION rotation;	//回転
};

class Coin : public GameObject {
public:
	/*!
	*@brief	コンストラクタ
	*/
	Coin();
	/*!
	*@brief	デストラクタ
	*/
	~Coin();
	/*!
	*@brief	初期化
	* @param[in]	numInstancing	インスタンスの数
	*/
	void Init(int numInstancing);
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
	/*!
	*@brief	インスタンシング描画用のワールド行列を初期化
	*/
	void InitInstancingWorldMatrix();
	/*!
	*@brief	インスタンシング描画用のワールド行列を更新
	*/
	void UpdateInstancingWorldMatrix();
	/*!
	*@brief	コインの座標と回転を保存
	*@param[in]		coinInfoList	コインのリスト
	*/
	void SetCoinInfoList(std::list<CoinInfo> coinInfoList)
	{
		m_coinInfoList = coinInfoList;
	}

private:
	SkinModel			m_model;				//スキンモデル
	SkinModelData		m_modelData;			//スキンモデルデータ
	Light				m_light;				//ライト
	D3DXVECTOR3			m_scale;				//拡大率
	D3DXVECTOR3			m_initPosition;			//初期座標
	bool				m_flag = false;			//コイン獲得フラグ
	float				m_moveSpeed = 0.05f;	//移動速度
	int					m_numInstancing = 0;	//インスタンシング描画する数
	std::list<CoinInfo> m_coinInfoList;			//コインのリスト
};