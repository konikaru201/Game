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
	//ビュー行列を取得
	const D3DXMATRIX& GetViewMatrix()
	{
		return camera.GetViewMatrix();
	}
	//プロジェクション行列を取得
	const D3DXMATRIX& GetViewProjectionMatrix()
	{
		return camera.GetProjectionMatrix();
	}
private:
	D3DXVECTOR3 toCameraPos;	//注視点から視点へのベクトル
	Camera camera;				//カメラインスタンス
	CameraCollisionSolver cameraCollisionSolver;	//カメラコリジョンインスタンス
	bool ResetFlg = false;	//カメラリセットフラグ
	float Angle = 0.0f;		//XZ方向の回転量
	float UpAngle = 0.0f;
	D3DXVECTOR3 currentEyePos;
};

extern GameCamera* gameCamera;