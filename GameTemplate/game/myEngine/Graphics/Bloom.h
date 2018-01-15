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
	LPD3DXEFFECT effect;												//シェーダーエフェクト
	CRenderTarget luminanceRenderTarget;								//輝度を抽出するためのレンダリングターゲット
	CRenderTarget downSamplingRenderTarget[2];
	static const int NUM_WEIGHTS = 8;									//ガウスブラーの重み
	float weights[NUM_WEIGHTS];											//ガウスブラーで使う重みテーブル
};