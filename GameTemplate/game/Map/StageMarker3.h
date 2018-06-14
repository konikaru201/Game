/*!
*@brief	ステージマーカークラス
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"

class StageMarker3 : public GameObject {
public:
	/*!
	*@brief	コンストラクタ
	*/
	StageMarker3();
	/*!
	*@brief	デストラクタ
	*/
	~StageMarker3();
	/*!
	*@brief	初期化
	* @param[in]	pos		座標
	* @param[in]	rot		回転
	*/
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation);
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
private:
	SkinModel		m_model;			//スキンモデル
	SkinModelData	m_modelData;		//スキンモデルデータ
	MeshCollider	m_meshCollider;		//メッシュコライダー
	RigidBody		m_rigidBody;		//剛体
	Light			m_light;			//ライト
	D3DXVECTOR3		m_position;			//座標
	D3DXQUATERNION	m_rotation;			//回転
	D3DXMATRIX		m_parentWorldMatrix;
	D3DXVECTOR3		m_childPosition;
	D3DXMATRIX		m_parentRotationMatrix;
	D3DXQUATERNION	m_childRotation;	
	bool			m_stageChange = false;
};
