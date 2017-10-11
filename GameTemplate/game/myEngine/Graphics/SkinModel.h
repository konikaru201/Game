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
	void Draw(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix);
	
	/*!
	*@brief	ワールド行列を更新。
	*@details
	* 後でCMotionクラスに移動させます。
	*@param[in]		trans	平行移動。
	*@param[in]		rot		回転。
	*@param[in]		scale	拡大。
	*/
	void UpdateWorldMatrix( const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale );
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
	//ワールド座標を取得
	D3DXMATRIX& GetWorldMatrix()
	{
		return worldMatrix;
	}
	//シャドウマップ作成フラグを設定
	//DrawShadowMap シャドウマップを描画するか
	//RecieveShadow シャドウレシーバーかどうか
	void SetDrawShadowMap(bool DrawShadowMap, bool RecieveShadow)
	{
		isDrawShadowMap = DrawShadowMap;
		isRecieveShadow = RecieveShadow;
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
	bool isDrawShadowMap = false;
	bool isRecieveShadow = false;
};
