/*!
*@brief	移動床１クラス
*/
#pragma once

#include "myEngine/Physics/BoxCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

class MoveFloor : public GameObject 
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	MoveFloor();
	/*!
	*@brief	デストラクタ
	*/
	~MoveFloor();
	/*!
	*@brief	初期化
	* @param[in]	pos		座標
	* @param[in]	rot		回転
	*/
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);
	/*!
	*@brief	更新する前に一度だけ呼ばれる関数
	*/
	bool Start();
	/*!
	*@brief	Update関数より前に呼ばれる更新関数
	*/
	void PreUpdate();
	/*!
	*@brief	更新
	*/
	void Update();
	/*!
	*@brief	描画
	*/
	void Render();
	/*!
	*@brief	移動
	*/
	void Move();
	/*!
	* @brief	床の座標の取得
	*@return	床の座標
	*/
	const D3DXVECTOR3& GetPosition()
	{
		return m_position;
	}
	/*!
	* @brief	床のワールド行列の取得
	*@return	床のワールド行列
	*/
	const D3DXMATRIX& GetWorldMatrix()
	{
		return m_model.GetWorldMatrix();
	}

private:
	SkinModel		m_model;			//スキンモデル
	SkinModelData	m_modelData;		//スキンモデルデータ
	RigidBody		m_rigidBody;		//剛体
	Light			m_light;			//ライト
	D3DXVECTOR3		m_position;			//座標
	D3DXQUATERNION	m_rotation;			//回転
	D3DXVECTOR3		m_moveSpeed;		//移動速度
	float			m_timer = 0.0f;		//タイマー
	bool			m_moveFlag = false;	//移動フラグ
};