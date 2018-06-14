/*!
* @brief	プレイヤーコントローラー。
*/

#pragma once

#include "CapsuleCollider.h"
#include "myEngine/Physics/RigidBody.h"

class ICollider;

static const float cPI = 3.14159265358979323846f;

class PlayerController {
public:
	PlayerController() {
		m_position = { 0.0f, 0.0f, 0.0f };
		m_moveSpeed = { 0.0f, 0.0f, 0.0f };
	}

	~PlayerController() 
	{
		if (m_collider != nullptr) {
			delete m_collider;
			m_collider = nullptr;
		}
	}
	/*!
	* @brief	初期化。
	*/
	void Init(ICollider* collider, const D3DXVECTOR3& position);
	/*!
	* @brief	実行。
	*/
	void Execute();
	/*!
	* @brief	座標を取得。
	*/
	const D3DXVECTOR3& GetPosition() const
	{
		return m_position;
	}
	/*!
	* @brief	座標を設定。
	*/
	void SetPosition(const D3DXVECTOR3& pos)
	{
		m_position = pos;
	}
	/*!
	* @brief	移動速度を設定。
	*/
	void SetMoveSpeed(const D3DXVECTOR3& speed)
	{
		m_moveSpeed = speed;
	}
	/*!
	* @brief	移動速度を取得。
	*/
	const D3DXVECTOR3& GetMoveSpeed() const
	{
		return m_moveSpeed;
	}
	/*!
	* @brief	ジャンプさせる。
	*/
	void Jump()
	{
		m_isJump = true;
		m_isOnGround = false;
	}
	/*!
	* @brief	ジャンプ中か判定
	*/
	bool IsJump() const
	{
		return m_isJump;
	}
	/*!
	* @brief	地面上にいるか判定。
	*/
	bool IsOnGround() const
	{
		return m_isOnGround;
	}
	/*!
	* @brief	壁に当たっているか判定。
	*/
	bool IsOnWall() const
	{
		return m_isOnWall;
	}
	/*!
	* @brief	移動床上にいるか判定。
	*/
	bool IsOnMoveFloor() const
	{
		return m_isOnMoveFloor;
	}
	/*!
	* @brief	移動床上にいるか判定。
	*/
	bool IsOnMoveFloor2() const
	{
		return m_isOnMoveFloor2;
	}
	/*!
	* @brief	スプリング上にいるか判定。
	*/
	bool IsOnSpring() const
	{
		return m_isOnSpring;
	}
	/*!
	* @brief	ブロック上にいるか判定。
	*/
	bool IsOnBlock() const
	{
		return m_isOnBlock;
	}
	/*!
	* @brief	ブロック2上にいるか判定。
	*/
	bool IsOnBlock2() const
	{
		return m_isOnBlock2;
	}
	/*!
	* @brief	ボックス上にいるか判定。
	*/
	bool IsOnBox() const
	{
		return m_isOnBox;
	}
	/*!
	* @brief	コライダーを取得。
	*/
	ICollider* GetCollider()
	{
		return m_collider;
	}
	/*!
	* @brief	重力を取得。
	*/
	void SetGravity(float gravity)
	{
		m_gravity = gravity;
	}
	/*!
	* @brief	壁の法線を取得。
	*/
	const D3DXVECTOR3& GethitNormal()
	{
		return m_hitNormal;
	}
	/*!
	* @brief	剛体を取得。
	*/
	RigidBody* GetRigidBody()
	{
		return &m_rigidBody;
	}
	/*!
	* @brief	剛体を物理エンジンから削除。。
	*/
	void RemoveRigidBoby();
	//レイの方向の状態
	enum RayDirection {
		RIGHT,	//右
		LEFT,	//左
		FRONT,	//前
		BACK,	//後
		DOWN,	//下
		UP,		//上
		NUM_RAY,	//レイの数。
	};
private:
	D3DXVECTOR3 		m_position;						//座標。
	D3DXVECTOR3 		m_moveSpeed;					//移動速度。
	bool 				m_isJump = false;				//ジャンプ中？
	bool				m_isOnGround = true;			//地面の上にいる？
	bool				m_isOnMoveFloor = false;		//移動床の上にいる？
	bool				m_isOnMoveFloor2 = false;		//移動床の上にいる？
	bool				m_isOnSpring = false;			//スプリングの上にいる？
	bool				m_isOnWall = false;
	bool				m_isOnBlock = false;
	bool				m_isOnBlock2 = false;
	bool				m_isOnBox = false;
	ICollider*			m_collider = nullptr;			//コライダー。
	RigidBody			m_rigidBody;					//剛体。
	float				m_gravity = -9.8f;				//重力。
	D3DXVECTOR3			m_hitNormal = { 0.0f,0.0f,0.0f };
	bool				m_hitCeiling = false;			//上方向に当たった
	RayDirection		rayDirection = RIGHT;
};