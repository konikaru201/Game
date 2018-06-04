#pragma once

#include "IPlayerState.h"
#include "myEngine/HID/Pad.h"
#include "Camera/GameCamera.h"

class PlayerMove : public IPlayerState {
public:
	//コンストラクタ
	PlayerMove(Player* player, PlayerStateMachine* psm) :
		IPlayerState(player, psm)
	{
	}

	//デストラクタ
	~PlayerMove()
	{
	}

	//更新
	void Update();

	//更新する前に一度だけ呼ばれる
	bool Start();

	//移動処理
	//戻り値　移動速度
	D3DXVECTOR3 Move();

	D3DXVECTOR3 Jump(const D3DXVECTOR3& speed);

	//回転
	void Turn();

private:
	float acceleration = 0.0f;						//加速度
	const float speedLimit = 6.0f;					//限界速度
	D3DXVECTOR3 dir = { 0.0f,0.0f,0.0f };			//方向
	D3DXVECTOR3 currentDir = { 0.0f,0.0f,0.0f };	//1フレーム前のZ方向
	int m_rotationFrameCount = 0;					//回転フレームカウント
	float timer = 0.0f;								//タイマー
};