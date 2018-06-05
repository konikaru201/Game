/*!
*@brief	床クラス
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Physics/BoxCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Graphics/Light.h"

class Floor : public GameObject{
public:
	/*!
	*@brief	コンストラクタ
	*/
	Floor();
	/*!
	*@brief	デストラクタ
	*/
	~Floor();
	/*!
	*@brief	初期化
	* @param[in]	pos		座標
	* @param[in]	rot		回転
	*/
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);
	/*!
	*@brief	更新
	*/
	void Update();
	/*!
	*@brief	描画
	*/
	void Render();

private:
	SkinModel		m_model;		//スキンモデル
	SkinModelData	m_modelData;	//スキンモデルデータ
	RigidBody		m_rigidBody;	//剛体
	Light			m_light;		//ライト
	D3DXVECTOR3		m_position;		//座標
	D3DXQUATERNION	m_rotation;		//回転
};