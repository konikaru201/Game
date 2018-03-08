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
	if (pad->IsTrigger(pad->enButtonLB1)) {
		m_cameraReset = true;
	}

	if (m_cameraReset) {
		D3DXVECTOR3 playerBack = player->GetPlayerDir();
		playerBack *= -1.0f;
		D3DXVECTOR3 toCameraPosition = toCameraPos;
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
			angle /= 10;

			D3DXMATRIX rot;
			D3DXMatrixIdentity(&rot);
			D3DXMatrixRotationAxis(&rot, &Cross, angle);
			D3DXVec3TransformCoord(&toCameraPos, &toCameraPos, &rot);
		}
	}

	//�X�e�[�W�N���A���Ƀv���C���[�̐��ʂɌ�������
	if (player->GetStar() && !m_stopRotation) {
		D3DXVECTOR3 playerForward = player->GetPlayerDir();
		D3DXVECTOR3 toCameraPosition = toCameraPos;
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