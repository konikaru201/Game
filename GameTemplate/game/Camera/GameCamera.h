#pragma once

#include "myEngine/Graphics/Camera.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/HID/Pad.h"
#include "myEngine/Physics/CameraCollisionSolver.h"

class GameCamera : public GameObject
{
public:
	//�R���X�g���N�^
	GameCamera();

	//�f�X�g���N�^
	~GameCamera();

	//������
	bool Start();

	//�X�V
	void Update();

	//�ړ�
	void Move();

	//���Z�b�g
	void Reset();

	//�����_��ݒ�
	void SetTarget(const D3DXVECTOR3& target)
	{
		camera.SetLookatPt(target);
	}
	//���_��ݒ�
	void SetPosition(const D3DXVECTOR3& position)
	{
		camera.SetEyePt(position);
	}
	//�����ʂ�ݒ�
	void SetFar(const float& _far)
	{
		camera.SetFar(_far);
	}
	//�A�X�y�N�g����擾
	float GetAspect()
	{
		return camera.GetAspect();
	}
	//��p���擾
	float GetAngle()
	{
		return camera.GetAngle();
	}
	//�����_���擾
	const D3DXVECTOR3& GetTarget()
	{
		return camera.GetLookatPt();
	}
	//���_���擾
	const D3DXVECTOR3& GetPosition()
	{
		return camera.GetEyePt();
	}
	//�O�������擾
	const D3DXVECTOR3& GetForward()
	{
		return camera.GetForwardVec();
	}
	//�E�������擾
	const D3DXVECTOR3& GetRight()
	{
		return camera.GetRightVec();
	}
	//�r���[�s����擾
	const D3DXMATRIX& GetViewMatrix()
	{
		return camera.GetViewMatrix();
	}
	//�v���W�F�N�V�����s����擾
	const D3DXMATRIX& GetProjectionMatrix()
	{
		return camera.GetProjectionMatrix();
	}
	//�J�����̃��Z�b�g�t���O���擾
	bool GetCameraReset()
	{
		return m_cameraReset;
	}

private:
	Camera camera;				//�J�����C���X�^���X
	CameraCollisionSolver cameraCollisionSolver;	//�J�����R���W�����C���X�^���X
	D3DXVECTOR3 toCameraPos;	//�����_���王�_�ւ̃x�N�g��
	bool ResetFlg = false;	//�J�������Z�b�g�t���O
	float UpAngle = 0.0f;
	D3DXVECTOR3 currentEyePos;
	int m_rotationFrameCount = 0;
	bool m_stopRotation = false;
	bool m_downRotation = false;
	bool m_upRotation = false;
	bool m_cameraReset = false;
};

extern GameCamera* gameCamera;