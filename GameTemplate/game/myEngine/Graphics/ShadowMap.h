/*!
*@brief	シャドウマップクラス
*/
#pragma once
#include "RenderTarget.h"

class CShadowMap {
public:
	/*!
	*@brief	コンストラクタ
	*/
	CShadowMap();
	/*!
	*@brief	デストラクタ
	*/
	~CShadowMap();
	/*!
	*@brief	テクスチャを取得
	*@param[in]		number		番号
	*@return	テクスチャ
	*/
	LPDIRECT3DTEXTURE9 GetTexture(int number)
	{
		return m_renderTarget[number].GetTexture();
	}
	/*!
	*@brief	初期化
	*/
	void Init();
	/*!
	*@brief	ライトビューの視点を設定
	*@param[in]		lightViewPosition		ライトビューの視点
	*/
	void SetLightViewPosition(const D3DXVECTOR3& lightViewPosition)
	{
		m_viewPosition = lightViewPosition;
	}
	/*!
	*@brief	ライトビューの注視点を設定
	*@param[in]		lightViewTarget		ライトビューの注視点
	*/
	void SetLightViewTarget(const D3DXVECTOR3& lightViewTarget)
	{
		m_viewTarget = lightViewTarget;
	}
	/*!
	*@brief	ライトビュー行列を取得
	*@param[in]		number		番号
	*@return	ライトビュー行列
	*/
	const D3DXMATRIX& GetLightViewMatrix(int number)
	{
		return m_lightViewMatrix[number];
	}
	/*!
	*@brief	ライトプロジェクション行列を取得
	*@param[in]		number		番号
	*@return	ライトプロジェクション行列
	*/
	const D3DXMATRIX& GetLightProjectionMatrix(int number)
	{
		return m_lightProjMatrix[number];
	}
	/*!
	*@brief	ライトビュープロジェクション行列を取得
	*@param[in]		number		番号
	*@return	ライトビュープロジェクション行列
	*/
	const D3DXMATRIX& GetLightViewProjectionMatrix(int number)
	{
		return m_LVPMatrix[number];
	}
	/*!
	*@brief	更新
	*/
	void Update();
	/*!
	*@brief	シャドウマップに書き込み
	*/
	void Draw();
private:
	static const int	NUM_SHADOW_MAP = 3;					//シャドウマップを作る数。
	CRenderTarget		m_renderTarget[NUM_SHADOW_MAP];		//シャドウマップを書きこむレンダリングターゲット。
	D3DXMATRIX			m_lightViewMatrix[NUM_SHADOW_MAP];	//ライトビューマトリクス。
	D3DXMATRIX			m_lightProjMatrix[NUM_SHADOW_MAP];	//ライトプロジェクションマトリクス。
	D3DXMATRIX			m_LVPMatrix[NUM_SHADOW_MAP];		//ライトビュープロジェクション行列。
	D3DXVECTOR3			m_viewPosition;						//ライトビューの視点。
	D3DXVECTOR3			m_viewTarget;						//ライトビューの注視点。
	D3DXVECTOR3			m_lightDirection;					//ライトの方向
	float				m_lightHeight = 1.0f;				//ライトの高さ
};

extern CShadowMap g_shadowMap;