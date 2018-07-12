/*!
*@brief	ギャラクシーボックスクラス
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"

class GalaxyBox : public GameObject {
public:
	/*!
	*@brief	コンストラクタ
	*/
	GalaxyBox();
	/*!
	*@brief	デストラクタ
	*/
	~GalaxyBox();
	/*!
	*@brief	初期化
	* @param[in]	pos		座標
	* @param[in]	rot		回転
	*/
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);
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
	*@brief	深度値を描画
	*/
	void RenderDepthValue();
private:
	SkinModel		m_model;			//スキンモデル
	SkinModelData	m_modelData;		//スキンモデルデータ
	D3DXVECTOR3		m_position;			//座標
	D3DXQUATERNION	m_rotation;			//回転
	Light			m_light;			//ライト

	LPDIRECT3DCUBETEXTURE9	m_cubeMapTexture = nullptr;	//キューブマップテクスチャ
};
