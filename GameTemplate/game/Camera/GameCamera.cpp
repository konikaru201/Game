#include "stdafx.h"
#include "GameCamera.h"
#include "Scene/GameScene.h"
#include "myEngine/HID/Pad.h"

GameCamera* gameCamera;

GameCamera::GameCamera()
{
}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	//�J����������
	m_camera.Init();
	m_camera.SetEyePt(D3DXVECTOR3(0.0f, 12.0f, 10.0f));
	m_camera.SetLookatPt(D3DXVECTOR3(0.0f, 10.5f, 3.0f));
	m_camera.SetFar(1000.0f);
	m_camera.Update();
	//�J�����̓����蔻���������
	m_cameraCollisionSolver.Init(0.2f);
	//�����_����J�����܂ł̃x�N�g�����v�Z�B
	m_toCameraPos = m_camera.GetEyePt() - m_camera.GetLookatPt();
	//�J�����̑O�������v�Z�B
	D3DXVECTOR3 cameraForward = m_camera.GetLookatPt() - m_camera.GetEyePt();
	D3DXVec3Normalize(&cameraForward, &cameraForward);
	m_camera.SetForwardVec(cameraForward);
	//�J�����̉E�������v�Z�B
	D3DXVECTOR3 cameraRight;
	D3DXVec3Cross(&cameraRight, &cameraForward, &m_camera.GetUpVec());
	m_camera.SetRightVec(cameraRight);

	return true;
}

void GameCamera::Update()
{
	Move();

	//�J�����̑O�������v�Z�B
	D3DXVECTOR3 cameraForward = m_camera.GetLookatPt() - m_camera.GetEyePt();
	D3DXVec3Normalize(&cameraForward, &cameraForward);
	m_camera.SetForwardVec(cameraForward);
	//�J�����̉E�������v�Z�B
	D3DXVECTOR3 cameraRight;
	D3DXVec3Cross(&cameraRight, &cameraForward, &m_camera.GetUpVec());
	m_camera.SetRightVec(cameraRight);

	//�J�����X�V
	m_camera.Update();
}

void GameCamera::Move()
{
	//�v���C���[�̍��W���擾
	D3DXVECTOR3 targetPos = player->GetPosition();
	targetPos.y += 0.5f;
	//�J�����̒����_��ݒ�
	m_camera.SetLookatPt(targetPos);

	if (!player->GetStar()) {
		//Y������̉�]�s����쐬
		D3DXMATRIX rot;
		//�P�ʍs����쐬
		D3DXMatrixIdentity(&rot);
		if (fabsf(pad->GetRStickXF()) > 0.0f) {		//����]
			D3DXMatrixRotationY(&rot, 0.03f * pad->GetRStickXF());
		}
		D3DXVec3TransformCoord(&m_toCameraPos, &m_toCameraPos, &rot);

		//�P�ʍs��ɂ���
		D3DXMatrixIdentity(&rot);
		D3DXVECTOR3 rotAxis;
		//�J�����̏�������擾
		D3DXVECTOR3 up = m_camera.GetUpVec();
		//��]�������߂�
		D3DXVec3Cross(&rotAxis, &up, &m_toCameraPos);
		//��]���𐳋K��
		D3DXVec3Normalize(&rotAxis, &rotAxis);
		if (fabsf(pad->GetRStickYF()) > 0.0f) {			//�c��]
			D3DXMatrixRotationAxis(&rot, &rotAxis, 0.03f * pad->GetRStickYF());
		}

		D3DXVECTOR3 toCameraPosOld = m_toCameraPos;
		D3DXVec3TransformCoord(&m_toCameraPos, &m_toCameraPos, &rot);
		D3DXVECTOR3 toCameraPosNormalize;
		D3DXVec3Normalize(&toCameraPosNormalize, &m_toCameraPos);
		if (fabsf(toCameraPosNormalize.x) < 0.1f && fabsf(toCameraPosNormalize.z) < 0.1f) {
			//����𒴂���
			m_toCameraPos = toCameraPosOld;
		}
	}

	//�J�������Z�b�g
	if (pad->IsTrigger(pad->enButtonLB1) && m_cameraReset == false) {
		m_cameraReset = true;
	}

	if (m_cameraReset) {
		D3DXVECTOR3 playerBack = player->GetPlayerDir();
		playerBack *= -1.0f;
		D3DXVECTOR3 toCameraPosition = m_toCameraPos;
		D3DXVec3Normalize(&toCameraPosition, &toCameraPosition);
		float angle = D3DXVec3Dot(&playerBack, &toCameraPosition);
		if (angle < -1.0f) {
			angle = -1.0f;
		}
		if (angle > 1.0f) {
			angle = 1.0f;
		}

		if (angle >= 0.999f) {
			m_cameraReset = false;
		}
		else {
			angle = acosf(angle);
			D3DXVECTOR3 Cross;
			D3DXVec3Cross(&Cross, &playerBack, &toCameraPosition);
			//�x�N�g���������������
			if (Cross.y > 0.0f) {
				angle *= -1.0f;
			}
			else if(Cross.y <= 0.0f) {
				angle *= -1.0f;
			}
			angle /= 5;

			D3DXMATRIX rot;
			D3DXMatrixIdentity(&rot);
			D3DXMatrixRotationAxis(&rot, &Cross, angle);
			D3DXVec3TransformCoord(&m_toCameraPos, &m_toCameraPos, &rot);
		}
	}

	//�X�e�[�W�N���A���Ƀv���C���[�̐��ʂɌ�������
	if (player->GetStar() && !m_stopRotation) {
		D3DXVECTOR3 playerForward = player->GetPlayerDir();
		D3DXVECTOR3 toCameraPosition = m_toCameraPos;
		D3DXVec3Normalize(&toCameraPosition, &toCameraPosition);
		float angle = D3DXVec3Dot(&playerForward, &toCameraPosition);
		if (angle < -1.0f) {
			angle = -1.0f;
		}
		if (angle > 1.0f) {
			angle = 1.0f;
		}

		if (angle >= 0.999f) {
			m_stopRotation = true;
		}
		else {
			angle = acosf(angle);
			D3DXVECTOR3 Cross;
			D3DXVec3Cross(&Cross, &playerForward, &toCameraPosition);
			//�x�N�g���������������
			if (Cross.y > 0.0f) {
				angle *= -1.0f;
			}
			else if(Cross.y <= 0.0f) {
				angle *= -1.0f;
			}
			angle /= 20;

			D3DXMATRIX rot;
			D3DXMatrixIdentity(&rot);
			D3DXMatrixRotationAxis(&rot, &Cross, angle);
			D3DXVec3TransformCoord(&m_toCameraPos, &m_toCameraPos, &rot);
		}
	}

	//�J�����̍��W
	D3DXVECTOR3 eyePos = targetPos + m_toCameraPos;

	if (!player->GetHitEnemy() && !player->GetFallPlayer()) {
		//�J�����̍��W��ۑ�
		m_currentEyePos = eyePos;
	}

	//�J�����̍��W��ݒ�
	m_camera.SetEyePt(m_currentEyePos);

	if (!player->GetStar() && !player->GetFallPlayer() && !player->GetHitEnemy()) {
		//�J�����̓����蔻��
		D3DXVECTOR3 newPos;
		if (m_cameraCollisionSolver.Execute(newPos, m_camera.GetEyePt(), m_camera.GetLookatPt()))
		{
			m_camera.SetEyePt(newPos);
		}
	}
}

void GameCamera::Reset()
{
	//�J����������
	m_camera.Init();
	m_camera.SetEyePt(D3DXVECTOR3(0.0f, 12.0f, 7.0f));
	m_camera.SetLookatPt(D3DXVECTOR3(0.0f, 10.5f, 0.0f));
	m_camera.Update();
	m_toCameraPos = m_camera.GetEyePt() - m_camera.GetLookatPt();
}