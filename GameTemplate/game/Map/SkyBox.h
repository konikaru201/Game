/*!
*@brief	スカイボックスクラス
*/
#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/GameObject/GameObject.h"

class SkyBox : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	SkyBox();
	/*!
	*@brief	デストラクタ
	*/
	~SkyBox();
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
private:
	SkinModel		m_model;			//スキンモデル
	SkinModelData	m_modelData;		//スキンモデルデータ
	MeshCollider	m_meshCollider;		//メッシュコライダー
	D3DXVECTOR3		m_position;			//座標
	D3DXQUATERNION	m_rotation;			//回転
	Light			m_light;			//ライト
	
	LPDIRECT3DCUBETEXTURE9	m_cubeMapTexture = nullptr;	//キューブマップテクスチャ
};