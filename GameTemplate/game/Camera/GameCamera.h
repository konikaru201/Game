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
	//�r���[�s����擾
	const D3DXMATRIX& GetViewMatrix()
	{
		return camera.GetViewMatrix();
	}
	//�v���W�F�N�V�����s����擾
	const D3DXMATRIX& GetViewProjectionMatrix()
	{
		return camera.GetProjectionMatrix();
	}
private:
	D3DXVECTOR3 toCameraPos;	//�����_���王�_�ւ̃x�N�g��
	Camera camera;				//�J�����C���X�^���X
	CameraCollisionSolver cameraCollisionSolver;	//�J�����R���W�����C���X�^���X
	bool ResetFlg = false;	//�J�������Z�b�g�t���O
	float Angle = 0.0f;		//XZ�����̉�]��
	float UpAngle = 0.0f;
	D3DXVECTOR3 currentEyePos;
};

extern GameCamera* gameCamera;