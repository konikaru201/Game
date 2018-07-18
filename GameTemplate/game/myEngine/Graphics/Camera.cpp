#include "stdafx.h"
#include "Camera.h"

//�R���X�g���N�^�B
Camera::Camera()
{
	Near = 1.0f;
	Far = 100.0f;
	aspect = (float)FRAME_BUFFER_WIDTH / (float)FRAME_BUFFER_HEIGHT;
	angle = D3DX_PI / 4;
}
//�f�X�g���N�^
Camera::~Camera()
{
}
//�A�X�y�N�g���ݒ�B
void Camera::SetAspect(float _aspect)
{
	aspect = _aspect;
}
//�A�X�y�N�g����擾�B
float Camera::GetAspect() const
{
	return aspect;
}
//��p��ݒ�
void Camera::SetAngle(float _angle)
{
	angle = _angle;
}
//��p���擾
float Camera::GetAngle() const
{
	return angle;
}
//�t�@�[��ݒ�B
void Camera::SetFar(float _far)
{
	Far = _far;
}
//�j�A�[�̎擾�B
float Camera::GetNear() const
{
	return Near;
}
//�t�@�[�̎擾�B
float Camera::GetFar() const
{
	return Far;
}
//�j�A�[��ݒ�B
void Camera::SetNear(float _near)
{
	Near = _near;
}
//���_�̃Z�b�^�[
void Camera::SetEyePt(const D3DXVECTOR3& pt)
{
	vEyePt = pt;
}
//���_�̃Q�b�^�[
const D3DXVECTOR3& Camera::GetEyePt() const
{
	return vEyePt;
}
//�����_�̃Z�b�^�[
void Camera::SetLookatPt(const D3DXVECTOR3& pt)
{
	vLookatPt = pt;
}
//�����_�̃Q�b�^�[�B
const D3DXVECTOR3& Camera::GetLookatPt() const
{
	return vLookatPt;
}
//�O�����̃Z�b�^�[
void Camera::SetForwardVec(const D3DXVECTOR3 & forward)
{
	vForward = forward;
}
//�O�����̃Q�b�^�[
const D3DXVECTOR3 & Camera::GetForwardVec() const
{
	return vForward;
}
//�E�����̃Z�b�^�[
void Camera::SetRightVec(const D3DXVECTOR3 & right)
{
	vRight = right;
}
//�E�����̃Q�b�^�[
const D3DXVECTOR3 & Camera::GetRightVec() const
{
	return vRight;
}
//������̃Z�b�^�[
void Camera::SetUpVec(const D3DXVECTOR3& up)
{
	vUpVec = up;
}
//������̃Q�b�^�[
const D3DXVECTOR3& Camera::GetUpVec() const
{
	return vUpVec;
}
//�r���[�s��̃Z�b�^�[�B
void Camera::SetViewMatrix(const D3DXMATRIX& mView)
{
	viewMatrix = mView;
}
//�r���[�s��̃Q�b�^�[
const D3DXMATRIX& Camera::GetViewMatrix() const
{
	return viewMatrix;
}
//�v���W�F�N�V�����s��̃Z�b�^�[
void Camera::SetProjectionMatrix(const D3DXMATRIX& mProj)
{
	projectionMatrix = mProj;
}
//�v���W�F�N�V�����s��̃Q�b�^�[
const D3DXMATRIX& Camera::GetProjectionMatrix() const
{
	return projectionMatrix;
}
//�J�����̍X�V�����B
void Camera::Update()
{
	D3DXMatrixLookAtLH(&viewMatrix, &vEyePt, &vLookatPt, &vUpVec);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, angle, aspect, Near, Far);
}
//�J�����̏������B
void Camera::Init()
{
	vEyePt = D3DXVECTOR3(0.0f, 0.5f, 2.0f);
	vLookatPt = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	Update();
}