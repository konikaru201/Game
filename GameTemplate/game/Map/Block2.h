/*!
*@brief	ブロック２クラス
*/
#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

class Block2 : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	Block2();
	/*!
	*@brief	デストラクタ
	*/
	~Block2();
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
	* @brief	ワールド行列を取得
	*@return	ワールド行列
	*/
	const D3DXMATRIX& GetWorldMatrix() const
	{
		return m_model.GetWorldMatrix();
	}
	/*!
	* @brief	回転行列を取得
	*@return	回転行列
	*/
	const D3DXMATRIX& GetRotationMatrix() const
	{
		return m_model.GetRotationMatrix();
	}
private:
	SkinModel		m_model;		//スキンモデル
	SkinModelData	m_modelData;	//スキンモデルデータ
	MeshCollider	m_meshCollider;	//メッシュコライダー
	RigidBody		m_rigidBody;	//剛体
	Light			m_light;		//ライト
	D3DXVECTOR3		m_rotationAxis; //回転軸
	D3DXVECTOR3		m_position;		//座標
	D3DXQUATERNION	m_rotation;		//回転
};