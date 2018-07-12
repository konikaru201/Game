/*!
*@brief	スキンモデル
*/
#pragma once

#include "myEngine/Graphics/Animation.h"

class SkinModelData;
class RenderContext;
class Light;
/*!
*@brief	スキンモデル
*/
class SkinModel {
public:
	SkinModel();
	~SkinModel();
	/*!
	*@brief	初期化
	*/
	void Init(SkinModelData* modelData);
	
	/*!
	*@brief	描画。
	*/
	void Draw(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix);
	
	/*!
	*@brief	ワールド行列を更新。
	*@param[in]		trans	平行移動。
	*@param[in]		rot		回転。
	*@param[in]		scale	拡大。
	*/
	void UpdateWorldMatrix( const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale );

	//インスタンシング描画のデータ作成
	void CreateInstancingDrawData(LPD3DXFRAME frame);

	/*!
	*@brief	ライトを設定。
	*/
	void SetLight(Light* light)
	{
		this->light = light;
	}
	//スペキュラマップを設定
	void SetSpecularMap(LPDIRECT3DTEXTURE9 specMap)
	{
		specularMap = specMap;
	}
	//法線マップを設定
	void SetNormalMap(LPDIRECT3DTEXTURE9 normalMap) 
	{
		this->normalMap = normalMap;
	}
	//キューブマップを設定
	void SetCubeMap(LPDIRECT3DCUBETEXTURE9 cubeMap)
	{
		this->cubeMap = cubeMap;
	}
	//ワールド座標を取得
	const D3DXMATRIX& GetWorldMatrix() const
	{
		return worldMatrix;
	}
	//回転行列を取得
	const D3DXMATRIX& GetRotationMatrix() const
	{
		return rotationMatrix;
	}
	//シャドウマップ作成フラグを設定
	//DrawShadowMap シャドウマップを描画するか
	//RecieveShadow シャドウレシーバーかどうか
	void SetDrawShadowMap(bool DrawShadowMap, bool RecieveShadow)
	{
		isDrawShadowMap = DrawShadowMap;
		isRecieveShadow = RecieveShadow;
	}
	//深度テストをするか設定
	void SetSilhouetteRender(bool SilhouetteRender)
	{
		isSilhouetteRender = SilhouetteRender;
	}
	//透明度を設定
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}
	//インスタンシング描画フラグを設定
	void SetInstancingDraw(bool isInstancingDraw)
	{
		m_isInstancingDraw = isInstancingDraw;
	}
	//インスタンシング描画する数を設定
	void SetNumInstancing(int numInstancing)
	{
		m_numInstancing = numInstancing;
	}
	//深度値描画フラグを設定
	void SetDepthValueDraw(bool isDepthValue)
	{
		m_isDepthValue = isDepthValue;
	}
	/*!
	*@brief	オリジナルメッシュの先頭を取得する。
	*/
	LPD3DXMESH GetOrgMeshFirst();
private:
	D3DXMATRIX			worldMatrix;				//!<ワールド行列。
	D3DXMATRIX			rotationMatrix;				//!<回転行列。
	SkinModelData*		skinModelData = nullptr;	//!<スキンモデルデータ。
	ID3DXEffect*		pEffect = nullptr;			//!<エフェクト。
	Animation			animation;					//!<アニメーション。
	Light*				light = nullptr;			//!<ライト。

	LPDIRECT3DTEXTURE9 specularMap = NULL;			//!<スペキュラマップ。
	LPDIRECT3DTEXTURE9 normalMap = NULL;			//!<法線マップ
	LPDIRECT3DCUBETEXTURE9 cubeMap = NULL;			//!<キューブマップ
	bool isDrawShadowMap = false;
	bool isRecieveShadow = false;
	bool isSilhouetteRender = false;
	bool m_isInstancingDraw = false;
	bool m_isDepthValue = false;
	float m_alpha = 1.0f;
	int m_numInstancing = 0;
};