/*!
*@brief	キラークラス
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"
#include "myEngine/Graphics/ParticleEmitter.h"
#include "myEngine/Physics/RigidBody.h"

class Killer : public GameObject {
public:
	/*!
	*@brief	コンストラクタ
	*/
	Killer();
	/*!
	*@brief	デストラクタ
	*/
	~Killer();
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
	/*!
	*@brief	移動速度を計算
	*@return 移動速度
	*/
	D3DXVECTOR3 Move();
	/*!
	*@brief	プレイヤーとの当たり判定
	* @param[in]	Length		距離
	* @param[in]	toPlayer	プレイヤーへのベクトル
	*/
	void CollisionDetection(float length , const D3DXVECTOR3& toPlayer);
	/*!
	* @brief	影を描画
	* @param[in]	viewMatrix		ビュー行列
	* @param[in]	projMatrix		プロジェクション行列
	* @param[in]	isDrawShadowMap	シャドウマップを描くフラグ
	* @param[in]	isRecieveShadow	シャドウレシーバーかどうか
	*/
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);
	/*!
	* @brief	キラーの向きを取得
	*@return	キラーの向き
	*/
	D3DXVECTOR3 GetDirection()
	{
		D3DXMATRIX matrix = m_model.GetWorldMatrix();
		D3DXVECTOR3 direction;
		direction.x = matrix.m[2][0];
		direction.y = matrix.m[2][1];
		direction.z = matrix.m[2][2];
		D3DXVec3Normalize(&direction, &direction);
		return direction;
	}
private:
	/*!
	*@brief	キラーの状態
	*/
	enum State {
		State_Search,	//探索
		State_Find,		//発見
		State_Miss,		//見失う
		State_Dead,		//死亡
		State_Hit,		//プレイヤーにヒット
	};

	State				m_state = State_Search;				//状態

	SkinModel			m_model;							//スキンモデル
	SkinModelData		m_modelData;						//スキンモデルデータ
	Light				m_light;							//ライト
	D3DXVECTOR3			m_position;							//座標
	D3DXQUATERNION		m_rotation;							//回転
	D3DXVECTOR3			m_initPosition;						//初期位置
	D3DXQUATERNION		m_initRotation;						//初期回転
	float				m_moveLimitLine[4];					//移動限界ライン
	RigidBody			m_rigidBody;						//剛体
	D3DXVECTOR3			m_moveDir = { 0.0f,0.0f,0.0f };		//見失ったときの移動方向
	const float			m_moveSpeed = 5.5f;					//移動速度
	bool				m_isDead = false;					//死亡フラグ
	bool				m_isRespawn = false;				//リスポーンフラグ
	float				m_timer = 0.0f;						//タイマー
	bool				m_hitPlayer = false;				//プレイヤーに当たったフラグ
	CParticleEmitter	m_particleEmitter;					//パーティクル生成
};