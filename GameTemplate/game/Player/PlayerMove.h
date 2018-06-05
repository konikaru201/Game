/*!
*@brief	移動ステート
*/
#pragma once

#include "IPlayerState.h"
#include "myEngine/HID/Pad.h"
#include "Camera/GameCamera.h"

class PlayerMove : public IPlayerState {
public:
	/*!
	*@brief	コンストラクタ
	* @param[in]	player		プレイヤー
	* @param[in]	psm			ステートマシン
	*/
	PlayerMove(Player* player, PlayerStateMachine* psm) :
		IPlayerState(player, psm)
	{
	}
	/*!
	*@brief	デストラクタ
	*/
	~PlayerMove()
	{
	}
	/*!
	*@brief	更新
	*/
	void Update();
	/*!
	*@brief	更新する前に一度だけ呼ばれる
	*/
	bool Start();
	/*!
	*@brief	移動速度を計算
	*@return 移動速度
	*/
	D3DXVECTOR3 Move();
	/*!
	*@brief	ジャンプ速度を計算
	*@return ジャンプ速度
	*/
	D3DXVECTOR3 Jump(const D3DXVECTOR3& speed);
	/*!
	*@brief	回転を計算
	*/
	void Turn();
private:
	float		m_acceleration = 0.0f;				//加速度
	const float m_speedLimit = 6.0f;				//限界速度
	D3DXVECTOR3 m_dir = { 0.0f,0.0f,0.0f };			//方向
	D3DXVECTOR3 m_currentDir = { 0.0f,0.0f,0.0f };	//1フレーム前のZ方向
	int			m_rotationFrameCount = 0;			//回転フレームカウント
	float		m_timer = 0.0f;						//タイマー
};