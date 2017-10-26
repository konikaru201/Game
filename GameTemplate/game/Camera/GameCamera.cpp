#include "stdafx.h"
#include "GameCamera.h"
#include "Scene/GameScene.h"
#include "myEngine/HID/Pad.h"

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	//カメラ初期化
	camera.Init();
	camera.SetEyePt(D3DXVECTOR3(0.0f, 12.0f, 7.0f));
	camera.SetLookatPt(D3DXVECTOR3(0.0f, 10.5f, 0.0f));
	camera.SetFar(1000.0f);
	camera.Update();
	cameraCollisionSolver.Init(0.2f);
	toCameraPos = camera.GetEyePt() - camera.GetLookatPt();

	return true;
}

void GameCamera::Update()
{
	if (gameScene == nullptr) { return; }
	Move();
	//カメラ更新
	camera.Update();
}

void GameCamera::Move()
{
	//Y軸周りの回転行列を作成
	D3DXMATRIX rot;
	//単位行列を作成
	D3DXMatrixIdentity(&rot);
	if (fabsf(pad->GetRStickXF()) > 0.0f) {		//横回転
		D3DXMatrixRotationY(&rot, 0.05f * pad->GetRStickXF());
	}
	D3DXVec3TransformCoord(&toCameraPos, &toCameraPos, &rot);

	//単位行列にする
	D3DXMatrixIdentity(&rot);
	D3DXVECTOR3 rotAxis;
	//カメラの上方向を取得
	D3DXVECTOR3 up = camera.GetUpVec();
	//回転軸を求める
	D3DXVec3Cross(&rotAxis, &up, &toCameraPos);
	//回転軸を正規化
	D3DXVec3Normalize(&rotAxis, &rotAxis);
	if (fabsf(pad->GetRStickYF()) > 0.0f) {			//縦回転
		D3DXMatrixRotationAxis(&rot, &rotAxis, 0.05f * pad->GetRStickYF());
	}

	D3DXVECTOR3 toCameraPosOld = toCameraPos;
	D3DXVec3TransformCoord(&toCameraPos, &toCameraPos, &rot);
	D3DXVECTOR3 toCameraPosNormalize;
	D3DXVec3Normalize(&toCameraPosNormalize, &toCameraPos);
	if (fabsf(toCameraPosNormalize.x) < 0.1f && fabsf(toCameraPosNormalize.z) < 0.1f) {
		//可動域を超えた
		toCameraPos = toCameraPosOld;
	}

	//プレイヤーの座標を取得
	D3DXVECTOR3 targetPos = g_player->GetPosition();
	targetPos.y += 0.5f;
	//カメラの注視点を設定
	camera.SetLookatPt(targetPos);

	//カメラリセット
	if (pad->IsTrigger(pad->enButtonLB1) && !ResetFlg) {
		////プレイヤーの向きを取得
		//D3DXVECTOR3 PlayerDir = g_player->GetPlayerDir();
		////向きを逆向きにする
		//D3DXVec3Scale(&PlayerDir, &PlayerDir, -1.0f);
		////プレイヤーの逆向きとプレイヤーからカメラの向きを正規化
		//D3DXVECTOR3 playerNormalizeDir;
		//D3DXVECTOR3 cameraNormalizePos;
		//D3DXVec3Normalize(&playerNormalizeDir, &PlayerDir);
		//D3DXVec3Normalize(&cameraNormalizePos, &toCameraPos);
		////二つのベクトルの角度を計算
		//float angle = D3DXVec3Dot(&playerNormalizeDir, &cameraNormalizePos);
		//angle = acosf(angle);
		////二つのベクトルに直交するベクトルを求める
		//D3DXVECTOR3 hoge;
		//D3DXVec3Cross(&hoge, &PlayerDir, &toCameraPos);
		////ベクトルが上向きか判定
		//if (hoge.y > 0.0f) {
		//	//回転方向を逆にする
		//	angle = angle * -1.0f;
		//}
		////回転量を記録
		//Angle = angle;

		////縦回転
		//D3DXVECTOR3 cameraNormalizePos;
		//D3DXVec3Normalize(&cameraNormalizePos, &toCameraPos);

		////D3DXVECTOR3 playerUpDir = { 0.0f,1.0f,0.0f };
		//D3DXVECTOR3 playerUpDir = g_player->GetPlayerUpDir();
		//float upAngle = D3DXVec3Dot(&playerUpDir, &cameraNormalizePos);
		//upAngle = acosf(upAngle);
		////D3DXVECTOR3 hogehoge;
		////D3DXVec3Cross(&hogehoge, &playerUpDir, &toCameraPos);
		////if (hogehoge.y > 0.0f) {
		////	upAngle = upAngle * -1.0f;
		////}
		//UpAngle = upAngle;

		//ResetFlg = true;
	}
	if (ResetFlg) {
		//D3DXVECTOR3 toCameraPosOld = toCameraPos;

		////横回転のリセット
		//{
		//	//回転量を分割する
		//	float divideAngle = Angle / 5.0f;
		//	D3DXMATRIX rot;
		//	D3DXMatrixRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), divideAngle);
		//	D3DXVec3TransformCoord(&toCameraPos, &toCameraPos, &rot);
		//}

		//D3DXVECTOR3 playerUpDir = g_player->GetPlayerUpDir();

		////縦方向のリセット
		//{
		//	float divideUpAngle = UpAngle / 3.0f;
		//	D3DXMATRIX rotUp;
		//	D3DXVECTOR3 RotAxis;
		//	D3DXVec3Cross(&RotAxis, /*&up,*/&playerUpDir , &toCameraPos);
		//	D3DXVec3Normalize(&RotAxis, &RotAxis);
		//	D3DXMatrixRotationAxis(&rotUp, &RotAxis, divideUpAngle);
		//	D3DXVec3TransformCoord(&toCameraPos, &toCameraPos, &rotUp);

		//	D3DXVECTOR3 toCameraPosNormalize;
		//	D3DXVec3Normalize(&toCameraPosNormalize, &toCameraPos);
		//	if (fabsf(toCameraPosNormalize.y) < 0.1f) {
		//		//可動域を超えた
		//		toCameraPos = toCameraPosOld;
		//		ResetFlg = false;
		//	}
		//}
	}

	//カメラの座標
	D3DXVECTOR3 eyePos = targetPos + toCameraPos;

	//カメラの座標を設定
	camera.SetEyePt(eyePos);

	////カメラの当たり判定
	//D3DXVECTOR3 newPos;
	//if (cameraCollisionSolver.Execute(newPos, camera.GetEyePt(), camera.GetLookatPt()))
	//{
	//	camera.SetEyePt(newPos);
	//}
}

void GameCamera::Reset()
{
	//カメラ初期化
	camera.Init();
	camera.SetEyePt(D3DXVECTOR3(0.0f, 12.0f, 7.0f));
	camera.SetLookatPt(D3DXVECTOR3(0.0f, 10.5f, 0.0f));
	camera.Update();
	toCameraPos = camera.GetEyePt() - camera.GetLookatPt();
}