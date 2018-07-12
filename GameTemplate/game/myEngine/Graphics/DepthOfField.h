/*!
*@brief	被写界深度クラス
*/
#pragma once

#include "RenderTarget.h"

class DepthOfField {
public:
	/*!
	*@brief	コンストラクタ
	*/
	DepthOfField();
	/*!
	*@brief	デストラクタ
	*/
	~DepthOfField();
	/*!
	*@brief	描画
	*/
	void Render();
	/*!
	*@brief	重みを計算
	*@param[in]	dispersion		重みの割合
	*/
	void UpdateWeight(float dispersion);
	/*!
	*@brief	被写界深度をするかどうか
	*/
	void SetDepthOfField(bool isDepthOfField)
	{
		m_isDepthOfField = isDepthOfField;
	}
private:
	static const int	NUM_WEIGHTS = 8;			//ガウスブラーの重み
	LPD3DXEFFECT		m_effect;					//シェーダーエフェクト
	CRenderTarget		m_depthValueRenderTarget;
	CRenderTarget		m_blurRenderTarget[2][2];
	CRenderTarget		m_combineRenderTarget[2];	//ぼかし合成用のレンダリングターゲット
	float				m_weights[NUM_WEIGHTS];		//ガウスブラーで使う重みテーブル
	bool				m_isDepthOfField = false;
};

extern DepthOfField* depthOfField;