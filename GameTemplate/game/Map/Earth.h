/*!
*@brief	地球クラス
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"

class Earth : public GameObject {
public:
	/*!
	*@brief	コンストラクタ
	*/
	Earth();
	/*!
	*@brief	デストラクタ
	*/
	~Earth();
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
	* @brief	ワールド行列を取得
	*@return	ワールド行列
	*/
	const D3DXMATRIX& GetWorldMatrix()
	{
		return m_model.GetWorldMatrix();
	}
	/*!
	* @brief	回転しているか判定
	*/
	bool GetIsRotate()
	{
		return m_isRotate;
	}
	/*!
	* @brief	座標の取得
	*@return	座標
	*/
	const D3DXVECTOR3& GetPosition() {
		return m_position;
	}
private:
	SkinModel		m_model;			//スキンモデル
	SkinModelData	m_modelData;		//スキンモデルデータ
	MeshCollider	m_meshCollider;		//メッシュコライダー
	RigidBody		m_rigidBody;		//剛体
	Light			m_light;			//ライト
	D3DXVECTOR3		m_position;			//座標
	D3DXQUATERNION	m_rotation;			//回転
	bool			m_isRotate = false;
};
