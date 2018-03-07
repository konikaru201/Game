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
	camera.Init();
	camera.SetEyePt(D3DXVECTOR3(0.0f, 12.0f, 10.0f));
	camera.SetLookatPt(D3DXVECTOR3(0.0f, 10.5f, 3.0f));
	//�e�X�g�p
	//camera.SetLookatPt(D3DXVECTOR3(0.0f, 12.0f, 8.0f));
	camera.SetFar(1000.0f);
	camera.Update();
	cameraCollisionSolver.Init(0.2f);
	toCameraPos = camera.GetEyePt() - camera.GetLookatPt();

	return true;
}

void GameCamera::Update()
{
	Move();

	//�J�����X�V
	camera.Update();
}

void GameCamera::Move()
{
	//�v���C���[�̍��W���擾
	D3DXVECTOR3 targetPos = player->GetPosition();
	targetPos.y += 0.5f;
	//�J�����̒����_��ݒ�
	camera.SetLookatPt(targetPos);

	if (!player->GetStar()) {
		//Y������̉�]�s����쐬
		D3DXMATRIX rot;
		//�P�ʍs����쐬
		D3DXMatrixIdentity(&rot);
		if (fabsf(pad->GetRStickXF()) > 0.0f) {		//����]
			D3DXMatrixRotationY(&rot, 0.03f * pad->GetRStickXF());
		}
		D3DXVec3TransformCoord(&toCameraPos, &toCameraPos, &rot);

		//�P�ʍs��ɂ���
		D3DXMatrixIdentity(&rot);
		D3DXVECTOR3 rotAxis;
		//�J�����̏�������擾
		D3DXVECTOR3 up = camera.GetUpVec();
		//��]�������߂�
		D3DXVec3Cross(&rotAxis, &up, &toCameraPos);
		//��]���𐳋K��
		D3DXVec3Normalize(&rotAxis, &rotAxis);
		if (fabsf(pad->GetRStickYF()) > 0.0f) {			//�c��]
			D3DXMatrixRotationAxis(&rot, &rotAxis, 0.03f * pad->GetRStickYF());
		}

		D3DXVECTOR3 toCameraPosOld = toCameraPos;
		D3DXVec3TransformCoord(&toCameraPos, &toCameraPos, &rot);
		D3DXVECTOR3 toCameraPosNormalize;
		D3DXVec3Normalize(&toCameraPosNormalize, &toCameraPos);
		if (fabsf(toCameraPosNormalize.x) < 0.1f && fabsf(toCameraPosNormalize.z) < 0.1f) {
			//����𒴂���
			toCameraPos = toCameraPosOld;
		}
	}

	//�J�������Z�b�g
	if (pad->IsTrigger(pad->enButtonLB1) && !ResetFlg) {
		////�v���C���[�̌������擾
		//D3DXVECTOR3 PlayerDir = g_player->GetPlayerDir();
		////�������t�����ɂ���
		//D3DXVec3Scale(&PlayerDir, &PlayerDir, -1.0f);
		////�v���C���[�̋t�����ƃv���C���[����J�����̌����𐳋K��
		//D3DXVECTOR3 playerNormalizeDir;
		//D3DXVECTOR3 cameraNormalizePos;
		//D3DXVec3Normalize(&playerNormalizeDir, &PlayerDir);
		//D3DXVec3Normalize(&cameraNormalizePos, &toCameraPos);
		////��̃x�N�g���̊p�x���v�Z
		//float angle = D3DXVec3Dot(&playerNormalizeDir, &cameraNormalizePos);
		//angle = acosf(angle);
		////��̃x�N�g���ɒ�������x�N�g�������߂�
		//D3DXVECTOR3 hoge;
		//D3DXVec3Cross(&hoge, &PlayerDir, &toCameraPos);
		////�x�N�g���������������
		//if (hoge.y > 0.0f) {
		//	//��]�������t�ɂ���
		//	angle = angle * -1.0f;
		//}
		////��]�ʂ��L�^
		//Angle = angle;

		////�c��]
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

		////����]�̃��Z�b�g
		//{
		//	//��]�ʂ𕪊�����
		//	float divideAngle = Angle / 5.0f;
		//	D3DXMATRIX rot;
		//	D3DXMatrixRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), divideAngle);
		//	D3DXVec3TransformCoord(&toCameraPos, &toCameraPos, &rot);
		//}

		//D3DXVECTOR3 playerUpDir = g_player->GetPlayerUpDir();

		////�c�����̃��Z�b�g
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
		//		//����𒴂���
		//		toCameraPos = toCameraPosOld;
		//		ResetFlg = false;
		//	}
		//}
	}

	if (player->GetStar() && !m_goalFlag) {
		D3DXVECTOR3 playerForward = player->GetPlayerDir();
		D3DXVECTOR3 toCameraPosition = toCameraPos;
		toCameraPosition.y = 0.0f;
		D3DXVec3Normalize(&toCameraPosition, &toCameraPosition);
		m_angle = D3DXVec3Dot(&playerForward, &toCameraPosition);
		if (m_angle < -1.0f)
		{
			m_angle = -1.0f;
		}
		if (m_angle > 1.0f)
		{
			m_angle = 1.0f;
		}

		if (m_angle >= 0.999f) {
			m_goalFlag = true;
		}
		else {
			m_angle = acosf(m_angle);
			D3DXVECTOR3 Cross;
			D3DXVec3Cross(&Cross, &playerForward, &toCameraPosition);
			//�x�N�g���������������
			if (Cross.y > 0.0f) {
				m_angle *= -1.0f;
			}
			m_angle /= 20;

			D3DXMATRIX rot;
			D3DXMatrixIdentity(&rot);
			D3DXMatrixRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), m_angle);
			D3DXVec3TransformCoord(&toCameraPos, &toCameraPos, &rot);
		}
	}

	//�J�����̍��W
	D3DXVECTOR3 eyePos = targetPos + toCameraPos;

	if (player->GetState() != player->State_Dead) {
		//�J�����̍��W��ۑ�
		currentEyePos = eyePos;
	}

	//�J�����̍��W��ݒ�
	camera.SetEyePt(currentEyePos);

	//�J�����̓����蔻��
	D3DXVECTOR3 newPos;
	if (cameraCollisionSolver.Execute(newPos, camera.GetEyePt(), camera.GetLookatPt()))
	{
		camera.SetEyePt(newPos);
	}
}

void GameCamera::Reset()
{
	//�J����������
	camera.Init();
	camera.SetEyePt(D3DXVECTOR3(0.0f, 12.0f, 7.0f));
	camera.SetLookatPt(D3DXVECTOR3(0.0f, 10.5f, 0.0f));
	camera.Update();
	toCameraPos = camera.GetEyePt() - camera.GetLookatPt();
}