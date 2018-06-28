/*!
*@brief	バネクラス
*/
#pragma once

#include "myEngine/Physics/MeshCollider.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

class Spring : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	Spring();
	/*!
	*@brief	デストラクタ
	*/
	~Spring();
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
	*@brief	プレイヤーとの当たり判定
	*/
	void CollisionDetection();
	/*!
	* @brief	移動速度を取得
	*@return	移動速度
	*/
	const D3DXVECTOR3& GetMoveSpeed() const
	{
		return m_jumpSpeed;
	}

private:
	SkinModel		m_model;								//スキンモデル
	SkinModelData	m_modelData;							//スキンモデルデータ
	MeshCollider	m_meshCollider;							//メッシュコライダー
	RigidBody		m_rigidBody;							//剛体
	Light			m_light;								//ライト
	D3DXVECTOR3		m_position;								//座標
	D3DXQUATERNION	m_rotation;								//回転
	D3DXVECTOR3		m_jumpSpeed = { 0.0f, 20.0f, 0.0f };	//ジャンプ速度

	D3DXMATRIX		m_parentWorldMatrix;						//移動床２のワールド行列
	D3DXVECTOR3		m_childPosition = { 0.0f,0.0f,0.0f };		//移動床２のローカル座標からみた座標
	bool			m_moveFloor2Find = false;					//移動床２を発見したか
	D3DXVECTOR3		m_moveFloor2Position = { 0.0f,0.0f,0.0f };	//移動床２の座標
};