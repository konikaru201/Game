/*!
*@brief	建物１クラス
*/
#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"

class Building_a : public GameObject {
public:
	/*!
	*@brief	コンストラクタ
	*/
	Building_a();
	/*!
	*@brief	デストラクタ
	*/
	~Building_a();
	/*!
	*@brief	初期化
	* @param[in]	pos		座標
	* @param[in]	rot		回転
	*/
	void Init(D3DXVECTOR3 position, D3DXQUATERNION rotation);
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
	RigidBody		m_rigidBody;		//剛体
	Light			m_light;			//ライト
	D3DXVECTOR3		m_position;			//座標
	D3DXQUATERNION	m_rotation;			//回転
};