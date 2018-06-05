/*!
*@brief	レッドドラゴンクラス
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Graphics/ParticleEmitter.h"
#include "myEngine/Graphics/Light.h"

class Red_Dragon : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	Red_Dragon();
	/*!
	*@brief	デストラクタ
	*/
	~Red_Dragon();
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
	* @param[in]	length		距離
	* @param[in]	toPlayer	プレイヤーへのベクトル
	*/
	void CollisionDetection(float length, const D3DXVECTOR3& toPlayer);
	/*!
	* @brief	影を描画
	* @param[in]	viewMatrix		ビュー行列
	* @param[in]	projMatrix		プロジェクション行列
	* @param[in]	isDrawShadowMap	シャドウマップを描くフラグ
	* @param[in]	isRecieveShadow	シャドウレシーバーかどうか
	*/
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);
	/*!
	* @brief	レッドドラゴンの向きを取得
	*@return	レッドドラゴンの向き
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
	*@brief	アニメーションの状態
	*/
	enum AnimationNo {
		AnimationWait,		//待機
		AnimationRun,		//走り移動
		AnimationAttack,	//攻撃
		AnimationDead,		//死亡
	};
	/*!
	*@brief	レッドドラゴンの状態
	*/
	enum State {
		State_Wait,		//待機
		State_Move,		//移動
		State_Find,		//発見
		State_Miss,		//見失う
		State_Attack,	//攻撃
		State_Dead,		//死亡
		State_Hit,		//プレイヤーにヒット
	};

	State				m_state = State_Wait;
	AnimationNo			m_currentAnim;
	AnimationNo			m_prevAnim;

	SkinModel			m_model;						//スキンモデル
	SkinModelData		m_modelData;					//スキンモデルデータ
	Light				m_light;						//ライト
	D3DXVECTOR3			m_position;						//座標
	D3DXVECTOR3			m_initPosition;					//初期座標
	D3DXQUATERNION		m_rotation;						//回転
	RigidBody			m_rigidBody;					//剛体
	Animation			m_animation;					//アニメーション
	D3DXVECTOR3			m_moveDir = { 0.0f,0.0f,0.0f };	//移動方向
	D3DXVECTOR3			m_up = { 0.0f,1.0f,0.0f };		//上方向
	float				m_moveSpeed = 2.0f;				//移動速度
	D3DXMATRIX*			m_matrix;						//ボーンのワールド行列
	float				m_timer = 0.0f;					//タイマー
	float				m_soundTimer = 0.0f;			//音のタイマー
	float				m_attackTimer = 0.0f;			//プレイヤーが攻撃に当たっている時間
	D3DXVECTOR3			m_XDir = { 1.0f,0.0f,0.0f };	//X方向
	bool				m_findAgainFlag = false;		//攻撃後に視界内にプレイヤーがいるか
	bool				m_changeDir = true;				//方向転換のフラグ
	CParticleEmitter	m_particleEmitter;				//パーティクル生成
	bool				m_hitPlayer = false;			//プレイヤーに当たったフラグ
	bool				m_isDead = false;				//死亡フラグ
};