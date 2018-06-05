/*!
*@brief	マップチップクラス
*/
#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"

class MapChip : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	MapChip();
	/*!
	*@brief	デストラクタ
	*/
	~MapChip();
	/*!
	*@brief	初期化
	* @param[in]	modelName		モデルネーム
	* @param[in]	position		座標
	* @param[in]	rotation		回転
	*/
	void Init(const char* modelName, D3DXVECTOR3 position, D3DXQUATERNION rotation);
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
};

