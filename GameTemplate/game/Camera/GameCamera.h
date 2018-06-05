/*!
*@brief	�Q�[���J�����N���X
*/
#pragma once

#include "myEngine/Graphics/Camera.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/HID/Pad.h"
#include "myEngine/Physics/CameraCollisionSolver.h"

class GameCamera : public GameObject
{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	GameCamera();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~GameCamera();
	/*!
	*@brief	�X�V����O�Ɉ�x�����Ă΂��
	*/
	bool Start();
	/*!
	*@brief	�X�V
	*/
	void Update();
	/*!
	*@brief	�ړ�
	*/
	void Move();
	/*!
	*@brief	���Z�b�g
	*/
	void Reset();
	/*!
	*@brief	�����_��ݒ�
	* @param[in]	target		�����_
	*/
	void SetTarget(const D3DXVECTOR3& target)
	{
		m_camera.SetLookatPt(target);
	}
	/*!
	*@brief	���_��ݒ�
	* @param[in]	position	���_
	*/
	void SetPosition(const D3DXVECTOR3& position)
	{
		m_camera.SetEyePt(position);
	}
	/*!
	*@brief	�����ʂ�ݒ�
	* @param[in]	_far		������
	*/
	void SetFar(const float& _far)
	{
		m_camera.SetFar(_far);
	}
	/*!
	*@brief	�A�X�y�N�g����擾
	* @return �A�X�y�N�g��
	*/
	float GetAspect()
	{
		return m_camera.GetAspect();
	}
	/*!
	*@brief	��p���擾
	* @return ��p
	*/
	float GetAngle()
	{
		return m_camera.GetAngle();
	}
	/*!
	*@brief	�����_���擾
	* @return �����_
	*/
	const D3DXVECTOR3& GetTarget()
	{
		return m_camera.GetLookatPt();
	}
	/*!
	*@brief	���_���擾
	* @return ���_
	*/
	const D3DXVECTOR3& GetPosition()
	{
		return m_camera.GetEyePt();
	}
	/*!
	*@brief	�O�������擾
	* @return �O����
	*/
	const D3DXVECTOR3& GetForward()
	{
		return m_camera.GetForwardVec();
	}
	/*!
	*@brief	�E�������擾
	* @return �E����
	*/
	const D3DXVECTOR3& GetRight()
	{
		return m_camera.GetRightVec();
	}
	/*!
	*@brief	�r���[�s����擾
	* @return �r���[�s��
	*/
	const D3DXMATRIX& GetViewMatrix()
	{
		return m_camera.GetViewMatrix();
	}
	/*!
	*@brief	�v���W�F�N�V�����s����擾
	* @return �v���W�F�N�V�����s��
	*/
	const D3DXMATRIX& GetProjectionMatrix()
	{
		return m_camera.GetProjectionMatrix();
	}
	/*!
	*@brief	�J�����̃��Z�b�g�t���O���擾
	*/
	bool GetCameraReset()
	{
		return m_cameraReset;
	}
private:
	Camera					m_camera;					//�J�����C���X�^���X
	CameraCollisionSolver	m_cameraCollisionSolver;	//�J�����R���W�����C���X�^���X
	D3DXVECTOR3				m_toCameraPos;				//�����_���王�_�ւ̃x�N�g��
	D3DXVECTOR3				m_currentEyePos;			//�v���C���[���S���̃J�����̍��W
	int						m_rotationFrameCount = 0;	//��]�t���[���J�E���g
	bool					m_stopRotation = false;		//��]�X�g�b�v�t���O
	bool					m_cameraReset = false;		//�J�������Z�b�g�t���O
};

extern GameCamera* gameCamera;