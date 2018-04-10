#pragma once
#include "RenderTarget.h"

//シャドウマップクラス。
class CShadowMap {
public:
	//コンストラクタ
	CShadowMap();

	//デストラクタ
	~CShadowMap();

	//テクスチャを取得。
	LPDIRECT3DTEXTURE9 GetTexture(int number)
	{
		return renderTarget[number].GetTexture();
	}

	//初期化。
	void Init();

	//ライトビューの視点を設定。
	void SetLightViewPosition(const D3DXVECTOR3& lightViewPosition)
	{
		viewPosition = lightViewPosition;
	}

	//ライトビューの注視点を設定。
	void SetLightViewTarget(const D3DXVECTOR3& lightViewTarget)
	{
		viewTarget = lightViewTarget;
	}

	//ライトビュー行列を取得。
	const D3DXMATRIX& GetLightViewMatrix(int number)
	{
		return lightViewMatrix[number];
	}

	//ライトプロジェクション行列を取得。
	const D3DXMATRIX& GetLightProjectionMatrix(int number)
	{
		return lightProjMatrix[number];
	}

	//ライトビュープロジェクション行列を取得
	const D3DXMATRIX& GetLightViewProjectionMatrix(int number)
	{
		return m_LVPMatrix[number];
	}

	//更新。
	void Update();

	//シャドウマップに書き込み。
	void Draw();
private:
	static const int NUM_SHADOW_MAP = 3;			//シャドウマップを作る数。
	CRenderTarget renderTarget[NUM_SHADOW_MAP];		//シャドウマップを書きこむレンダリングターゲット。
	D3DXMATRIX  lightViewMatrix[NUM_SHADOW_MAP];	//ライトビューマトリクス。
	D3DXMATRIX	lightProjMatrix[NUM_SHADOW_MAP];	//ライトプロジェクションマトリクス。
	D3DXMATRIX  m_LVPMatrix[NUM_SHADOW_MAP];		//ライトビュープロジェクション行列。
	D3DXVECTOR3 viewPosition;						//ライトビューの視点。
	D3DXVECTOR3 viewTarget;							//ライトビューの注視点。
	D3DXVECTOR3 m_lightDirection;					//ライトの方向
	float		m_lightHeight = 1.0f;				//ライトの高さ
};

extern CShadowMap g_shadowMap;