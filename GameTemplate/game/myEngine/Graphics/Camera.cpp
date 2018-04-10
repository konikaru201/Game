#include "stdafx.h"
#include "Camera.h"

//コンストラクタ。
Camera::Camera()
{
	Near = 0.1f;
	Far = 100.0f;
	aspect = (float)FRAME_BUFFER_WIDTH / (float)FRAME_BUFFER_HEIGHT;
	angle = D3DX_PI / 4;
}
//デストラクタ
Camera::~Camera()
{
}
//アスペクト比を設定。
void Camera::SetAspect(float _aspect)
{
	aspect = _aspect;
}
//アスペクト比を取得。
float Camera::GetAspect()
{
	return aspect;
}
//画角を設定
void Camera::SetAngle(float _angle)
{
	angle = _angle;
}
//画角を取得
float Camera::GetAngle()
{
	return angle;
}
//ファーを設定。
void Camera::SetFar(float _far)
{
	Far = _far;
}
//ニアーの取得。
float Camera::GetNear()
{
	return Near;
}
//ファーの取得。
float Camera::GetFar()
{
	return Far;
}
//ニアーを設定。
void Camera::SetNear(float _near)
{
	Near = _near;
}
//視点のセッター
void Camera::SetEyePt(const D3DXVECTOR3& pt)
{
	vEyePt = pt;
}
//視点のゲッター
const D3DXVECTOR3& Camera::GetEyePt()
{
	return vEyePt;
}
//注視点のセッター
void Camera::SetLookatPt(const D3DXVECTOR3& pt)
{
	vLookatPt = pt;
}
//注視点のゲッター。
const D3DXVECTOR3& Camera::GetLookatPt()
{
	return vLookatPt;
}
//前方向のセッター
void Camera::SetForwardVec(const D3DXVECTOR3 & forward)
{
	vForward = forward;
}
//前方向のゲッター
const D3DXVECTOR3 & Camera::GetForwardVec()
{
	return vForward;
}
//右方向のセッター
void Camera::SetRightVec(const D3DXVECTOR3 & right)
{
	vRight = right;
}
//右方向のゲッター
const D3DXVECTOR3 & Camera::GetRightVec()
{
	return vRight;
}
//上方向のセッター
void Camera::SetUpVec(const D3DXVECTOR3& up)
{
	vUpVec = up;
}
//上方向のゲッター
const D3DXVECTOR3& Camera::GetUpVec()
{
	return vUpVec;
}
//ビュー行列のセッター。
void Camera::SetViewMatrix(const D3DXMATRIX& mView)
{
	viewMatrix = mView;
}
//ビュー行列のゲッター
const D3DXMATRIX& Camera::GetViewMatrix()
{
	return viewMatrix;
}
//プロジェクション行列のセッター
void Camera::SetProjectionMatrix(const D3DXMATRIX& mProj)
{
	projectionMatrix = mProj;
}
//プロジェクション行列のゲッター
const D3DXMATRIX& Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}
//カメラの更新処理。
void Camera::Update()
{
	D3DXMatrixLookAtLH(&viewMatrix, &vEyePt, &vLookatPt, &vUpVec);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, angle, aspect, Near, Far);
}
//カメラの初期化。
void Camera::Init()
{
	vEyePt = D3DXVECTOR3(0.0f, 0.5f, 2.0f);
	vLookatPt = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	Update();
}