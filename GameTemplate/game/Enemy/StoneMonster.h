/*!
*@brief	ストーンモンスタークラス
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"
#include "myEngine/Physics/RigidBody.h"
#include "myEngine/Physics/CharacterController.h"
#include "StoneMonsterStateMachine.h"

class StoneMonster : public GameObject
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	StoneMonster();
	/*!
	*@brief	デストラクタ
	*/
	~StoneMonster();
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
	* @brief	影を描画
	* @param[in]	viewMatrix		ビュー行列
	* @param[in]	projMatrix		プロジェクション行列
	* @param[in]	isDrawShadowMap	シャドウマップを描くフラグ
	* @param[in]	isRecieveShadow	シャドウレシーバーかどうか
	*/
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);
	/*!
	* @brief	シルエットの描画
	* @param[in]	viewMatrix		ビュー行列
	* @param[in]	projMatrix		プロジェクション行列
	*/
	void SilhouetteRender(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix);
	/*!
	* @brief	ストーンモンスターの座標の取得
	*@return	ストーンモンスターの座標
	*/
	const D3DXVECTOR3& GetPosition()
	{
		return m_position;
	}
	/*!
	*@brief	座標の設定
	* @param[in]	position		座標
	*/
	void SetPosition(const D3DXVECTOR3& position)
	{
		m_position = position;
	}
	/*!
	* @brief	回転を取得
	*@return	回転
	*/
	const D3DXQUATERNION& GetRotation()
	{
		return m_rotation;
	}
	/*!
	*@brief	回転を設定
	* @param[in]	rotation		回転
	*/
	void SetRotation(const D3DXQUATERNION& rotation)
	{
		m_rotation = rotation;
	}
	/*!
	* @brief	ストーンモンスターの向きを取得
	*@return	ストーンモンスターの向き
	*/
	const D3DXVECTOR3& GetDirection()
	{
		D3DXMATRIX matrix = m_model.GetWorldMatrix();
		m_direction.x = matrix.m[2][0];
		m_direction.y = matrix.m[2][1];
		m_direction.z = matrix.m[2][2];
		D3DXVec3Normalize(&m_direction, &m_direction);
		return m_direction;
	}
	/*!
	* @brief	移動速度を取得
	*@return	移動速度
	*/
	const D3DXVECTOR3& GetMoveSpeed()
	{
		return m_characterController.GetMoveSpeed();
	}
	/*!
	*@brief	移動速度を設定
	* @param[in]	moveSpeed	移動速度
	*/
	void SetMoveSpeed(const D3DXVECTOR3& moveSpeed)
	{
		m_moveSpeed = moveSpeed;
	}
	/*!
	*@brief	踏まれたフラグを取得
	*/
	bool GetIsStepOn()
	{
		return m_isStepOn;
	}
	/*!
	*@brief	移動床１の上にいるか判定
	*/
	bool GetIsOnMoveFloor()
	{
		return m_moveFloorHit;
	}
	/*!
	*@brief	移動床２の上にいるか判定
	*/
	bool GetIsOnMoveFloor2()
	{
		return m_moveFloor2Hit;
	}
	/*!
	* @brief	移動床１の座標を取得
	*@return	移動床１の座標
	*/
	const D3DXVECTOR3& GetMoveFloorPosition()
	{
		return m_moveFloorPosition;
	}
	/*!
	* @brief	移動床２の座標を取得
	*@return	移動床２の座標
	*/
	const D3DXVECTOR3& GetMoveFloor2Position()
	{
		return m_moveFloor2Position;
	}
private:
	SkinModel					m_model;							//スキンモデル
	SkinModelData				m_modelData;						//スキンモデルデータ
	Light						m_light;							//ライト
	D3DXVECTOR3					m_position;							//座標
	D3DXQUATERNION				m_rotation;							//回転
	D3DXVECTOR3					m_scale;							//拡大
	D3DXVECTOR3					m_direction;						//向き
	Animation					m_animation;						//アニメーション
	D3DXVECTOR3					m_moveSpeed = { 0.0f,0.0f,0.0f };	//移動速度
	CharacterController			m_characterController;				//キャラクターコントローラー
	StoneMonsterStateMachine	m_stoneMonsterStateMachine;			//ステートマシン

	D3DXMATRIX					m_parentWorldMatrix;						//移動床１のワールド行列
	D3DXVECTOR3					m_childPosition = { 0.0f,0.0f,0.0f };		//移動床１のローカル座標からみた座標
	bool						m_moveFloorHit = false;						//移動床１の上にいるか
	D3DXVECTOR3					m_moveFloorPosition = { 0.0f,0.0f,0.0f };	//移動床１の座標

	D3DXMATRIX					m_secondParentWorldMatrix;					//移動床２のワールド行列
	D3DXVECTOR3					m_secondChildPosition = { 0.0f,0.0f,0.0f };	//移動床２のローカル座標からみたプレイヤーの座標
	bool						m_moveFloor2Hit = false;					//移動床２の上にいるか
	D3DXVECTOR3					m_moveFloor2Position = { 0.0f,0.0f,0.0f };	//移動床２の座標

	float						m_deadTimer = 0.0f;					//死亡してからのタイマー
	bool						m_isStepOn = false;					//踏まれたフラグ
	bool						m_isHitPlaer = false;				//プレイヤーに当たったか
};