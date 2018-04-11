#pragma once

#include "myEngine/Graphics/Camera.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/HID/Pad.h"
#include "myEngine/Physics/CameraCollisionSolver.h"

class GameCamera : public GameObject
{
public:
	//コンストラクタ
	GameCamera();

	//デストラクタ
	~GameCamera();

	//初期化
	bool Start();

	//更新
	void Update();

	//移動
	void Move();

	//リセット
	void Reset();

	//注視点を設定
	void SetTarget(const D3DXVECTOR3& target)
	{
		camera.SetLookatPt(target);
	}
	//視点を設定
	void SetPosition(const D3DXVECTOR3& position)
	{
		camera.SetEyePt(position);
	}
	//遠平面を設定
	void SetFar(const float& _far)
	{
		camera.SetFar(_far);
	}
	//アスペクト比を取得
	float GetAspect()
	{
		return camera.GetAspect();
	}
	//画角を取得
	float GetAngle()
	{
		return camera.GetAngle();
	}
	//注視点を取得
	const D3DXVECTOR3& GetTarget()
	{
		return camera.GetLookatPt();
	}
	//視点を取得
	const D3DXVECTOR3& GetPosition()
	{
		return camera.GetEyePt();
	}
	//前方向を取得
	const D3DXVECTOR3& GetForward()
	{
		return camera.GetForwardVec();
	}
	//右方向を取得
	const D3DXVECTOR3& GetRight()
	{
		return camera.GetRightVec();
	}
	//ビュー行列を取得
	const D3DXMATRIX& GetViewMatrix()
	{
		return camera.GetViewMatrix();
	}
	//プロジェクション行列を取得
	const D3DXMATRIX& GetProjectionMatrix()
	{
		return camera.GetProjectionMatrix();
	}
	//カメラのリセットフラグを取得
	bool GetCameraReset()
	{
		return m_cameraReset;
	}

private:
	Camera camera;				//カメラインスタンス
	CameraCollisionSolver cameraCollisionSolver;	//カメラコリジョンインスタンス
	D3DXVECTOR3 toCameraPos;	//注視点から視点へのベクトル
	bool ResetFlg = false;	//カメラリセットフラグ
	float UpAngle = 0.0f;
	D3DXVECTOR3 currentEyePos;
	int m_rotationFrameCount = 0;
	bool m_stopRotation = false;
	bool m_downRotation = false;
	bool m_upRotation = false;
	bool m_cameraReset = false;
};

extern GameCamera* gameCamera;