#pragma once

#include "RenderTarget.h"

class Bloom {
public:
	//コンストラクタ
	Bloom();

	//デストラクタ
	~Bloom();

	//描画
	void Render();

	//重みを計算
	void UpdateWeight(float dispersion);
private:
	static const int NUM_WEIGHTS = 8;				//ガウスブラーの重み
	static const int NUM_DOWN_SAMPLING_COUNT = 5;	//ダウンサンプリングする回数
	LPD3DXEFFECT m_effect;							//シェーダーエフェクト
	CRenderTarget m_luminanceRenderTarget;			//輝度を抽出するためのレンダリングターゲット
	CRenderTarget m_combineRenderTarget;			//ぼかし合成用のレンダリングターゲット
	CRenderTarget m_downSamplingRenderTarget[NUM_DOWN_SAMPLING_COUNT][2]; //ダウンサンプリング用のレンダリングターゲット
	float m_weights[NUM_WEIGHTS];					//ガウスブラーで使う重みテーブル
};