#include "stdafx.h"
#include "StoneMonsterIdle.h"
#include "StoneMonster.h"
#include "Player/Player.h"
#include "myEngine/Timer/Timer.h"
#include <time.h>
#include <stdlib.h>

void StoneMonsterIdle::Update()
{
	//プレイヤーを探す
	Search();

	//移動
	Move();

	//移動し始めたら
	if (isMove) {
		//回転
		Turn();
	}

	//見つかっていたら
	if (GetIsFind()){
		m_sms->ChangeState(StoneMonsterState::enState_Follow);
		SetIsFind(false);
	}
}

bool StoneMonsterIdle::Start()
{
	//一度だけ乱数の初期化する
	srand((unsigned)time(NULL));

	m_destination = m_stoneMonster->GetPosition();
	m_initPosition = m_stoneMonster->GetPosition();

	timer = 0.0f;
	isMove = false;

	return true;
}

void StoneMonsterIdle::Move()
{
	m_moveSpeed = m_stoneMonster->GetMoveSpeed();

	//座標を取得
	D3DXVECTOR3 position = m_stoneMonster->GetPosition();
	//移動先までの距離を計算
	D3DXVECTOR3 toDestination = m_destination - position;
	float length = D3DXVec3Length(&toDestination);
	//移動先との距離が近い
	if (length <= 0.6f) {
		timer += Timer::GetFrameDeltaTime();
		if (timer >= 2.0f) {
			//ランダムに移動先を決定
			//0.0～1.0の値に変換
			float randomPositionX, randomPositionZ;
			randomPositionX = (float)rand() / 32767.0;
			randomPositionZ = (float)rand() / 32767.0;
			//0.0～6.0の値に変換
			randomPositionX *= 6.0f;
			randomPositionZ *= 6.0f;
			//-3.0～3.0の値に変換
			randomPositionX -= 3.0f;
			randomPositionZ -= 3.0f;
			//現在の座標から移動先までのベクトルを計算
			D3DXVECTOR3 toRandomPosition;
			toRandomPosition.x = m_initPosition.x + randomPositionX;
			toRandomPosition.y = 0.0f;
			toRandomPosition.z = m_initPosition.z + randomPositionZ;

			//移動先の座標を保存
			m_destination.x = m_initPosition.x + randomPositionX;
			m_destination.y = m_initPosition.y;
			m_destination.z = m_initPosition.z + randomPositionZ;

			//移動速度を計算
			D3DXVec3Normalize(&toRandomPosition, &toRandomPosition);
			toRandomPosition *= m_speed;
			m_moveSpeed.x = toRandomPosition.x;
			m_moveSpeed.z = toRandomPosition.z;
			//タイマーを初期化
			timer = 0.0f;
			isMove = true;
		}
		else {
			//動かない
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;
		}
	}
	else {
		//移動先に進む
		D3DXVec3Normalize(&toDestination, &toDestination);
		toDestination *= m_speed;
		m_moveSpeed.x = toDestination.x;
		m_moveSpeed.z = toDestination.z;
	}

	m_stoneMonster->SetMoveSpeed(m_moveSpeed);
}

void StoneMonsterIdle::Search()
{
	//プレイヤーの座標を取得
	D3DXVECTOR3 playerPos = player->GetPosition();
	//自身からプレイヤーのベクトルを計算
	D3DXVECTOR3 toPlayerDir = playerPos - m_stoneMonster->GetPosition();
	//プレイヤーとの距離を計算
	float length = D3DXVec3Length(&toPlayerDir);
	toPlayerDir.y = 0.0f;
	//自身からプレイヤーへの角度を計算
	D3DXVec3Normalize(&toPlayerDir, &toPlayerDir);
	D3DXVECTOR3 forward = m_stoneMonster->GetDirection();
	float angle = D3DXVec3Dot(&toPlayerDir, &forward);
	angle = acosf(angle);

	if (fabsf(angle) < D3DXToRadian(30.0f) && length < 6.0f || length < 3.0f)
	{
		//発見された
		SetIsFind(true);
	}
}

void StoneMonsterIdle::Turn()
{
	D3DXQUATERNION rot;
	D3DXQuaternionIdentity(&rot);
	m_rotationFrameCount++;
	//モデルの前方向を取得
	D3DXVECTOR3 forward = m_stoneMonster->GetDirection();
	D3DXVec3Normalize(&forward, &forward);
	//座標を取得
	D3DXVECTOR3 position = m_stoneMonster->GetPosition();
	//移動先へのベクトルを計算
	D3DXVECTOR3 toDestination = m_destination - position;
	toDestination.y = 0.0f;
	D3DXVec3Normalize(&toDestination, &toDestination);
	float angle = D3DXVec3Dot(&forward, &toDestination);
	if (angle < -1.0f) {
		angle = -1.0f;
	}
	if (angle > 1.0f)
	{
		angle = 1.0f;
	}
	angle = acosf(angle);
	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &forward, &toDestination);
	if (Cross.y < 0.0f) {
		angle *= -1.0f;
	}
	angle /= 3;
	if (m_rotationFrameCount <= 3) {
		D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);
		D3DXQUATERNION rotation = m_stoneMonster->GetRotation();
		D3DXQuaternionMultiply(&rotation, &rotation, &rot);
		m_stoneMonster->SetRotation(rotation);
	}
	else {
		m_rotationFrameCount = 0;
	}
}
