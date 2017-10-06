#pragma once

#include "SphereCollider.h"

class CameraCollisionSolver {
public:
	//�R���X�g���N�^
	CameraCollisionSolver();

	//�f�X�g���N�^
	~CameraCollisionSolver();

	//������
	//radius	�J�����̃o�E���f�B���O�X�t�B�A�̔��a
	void Init(float radius);

	//�R���W���������̎��s
	//result	�R���W�����������s�������ʂ̃J�����̎��_�̍��W���i�[�����
	//posiiton	�J�����̎��_
	//target	�J�����̒����_
	//return	�R���W�����������s�����ꍇ��true���Ԃ��Ă���
	bool Execute(D3DXVECTOR3& result, const D3DXVECTOR3& position, const D3DXVECTOR3& target);
private:
	SphereCollider	m_collider;		 //�R���C�_�[
	float			m_radius = 0.0f; //���a
};