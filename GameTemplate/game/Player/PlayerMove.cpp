#include "stdafx.h"
#include "PlayerMove.h"
#include "Player.h"
#include "myEngine/sound/SoundSource.h"
#include "myEngine/GameObject/GameObjectManager.h"

void PlayerMove::Update()
{	
	bool cameraRiset = false;
	//�J�����̃��Z�b�g���͓����Ȃ�
	if (gameCamera != nullptr && !gameCamera->GetCameraReset()) {
		//�ړ����x�ƕ�����ݒ�
		m_player->SetMoveSpeed(Move());
	
		if (pad->GetLStickXF() != 0.0f || pad->GetLStickYF() != 0.0f) {
			//��]
			Turn();
		}

		if (m_player->GetIsJump()) {
			//�W�����v�A�j���[�V������ݒ�
			m_currentAnim = AnimationJump;
		}
		else {
			//����A�j���[�V������ݒ�
			m_currentAnim = AnimationRun;
			timer += Timer::GetFrameDeltaTime();

			if (timer >= 0.4f) {
				CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
				SE->Init("Assets/sound/FootStep.wav");
				SE->Play(false);
				timer = 0.0f;
			}
		}
		//�A�j���[�V�����̐ݒ�
		m_player->SetCurrentAnim(m_currentAnim);
	}
	else {
		D3DXVECTOR3 moveSpeed = { 0.0f,0.0f,0.0f };
		m_player->SetMoveSpeed(moveSpeed);
		cameraRiset = true;
	}

	if (acceleration == 0.0f && !m_player->GetIsJump()) {
		m_psm->ChangeState(PlayerState::plState_Idle);
	}
	else if (m_player->GetHitEnemy() || m_player->GetFallPlayer()) {
		m_psm->ChangeState(PlayerState::plState_Dead);
	}
	else if (m_player->GetStar()) {
		m_psm->ChangeState(PlayerState::plState_GetStar);
	}
}

bool PlayerMove::Start()
{
	return true;
}

D3DXVECTOR3 PlayerMove::Move()
{
	//�ړ����x���擾
	D3DXVECTOR3 moveSpeed = m_player->GetMoveSpeed();

	//�X�e�B�b�N�̓��͗ʂ��擾
	D3DXVECTOR3 moveDir;
	moveDir.y = 0.0f;
	moveDir.x = pad->GetLStickXF();
	moveDir.z = pad->GetLStickYF();

	//�J�����̋t�s����쐬
	D3DXMATRIX ViewMatrix = gameCamera->GetViewMatrix();
	D3DXMATRIX ViewMatrixInv;
	D3DXMatrixInverse(&ViewMatrixInv, 0, &ViewMatrix);

	//�J������Ԃ��猩���������̃x�N�g��
	D3DXVECTOR3 cameraVecZ;
	cameraVecZ.x = ViewMatrixInv.m[2][0];
	cameraVecZ.y = 0.0f;
	cameraVecZ.z = ViewMatrixInv.m[2][2];
	D3DXVec3Normalize(&cameraVecZ, &cameraVecZ);

	//�J������Ԃ��猩���������̃x�N�g��
	D3DXVECTOR3 cameraVecX;
	cameraVecX.x = ViewMatrixInv.m[0][0];
	cameraVecX.y = 0.0f;
	cameraVecX.z = ViewMatrixInv.m[0][2];
	D3DXVec3Normalize(&cameraVecX, &cameraVecX);

	//�L�����N�^�[�̌������v�Z
	dir.x = cameraVecX.x * moveDir.x + cameraVecZ.x * moveDir.z;
	dir.y = 0.0f;
	dir.z = cameraVecX.z * moveDir.x + cameraVecZ.z * moveDir.z;

	//������90�x�ȏ�ς�����瑬�x��������
	if (D3DXVec3Dot(&currentDir, &dir) < -0.1f) {
		acceleration = 1.0f;
	}

	//1�t���[���O�̌�����ۑ�
	currentDir = dir;

	//�ړ����Ă�Ȃ珙�X�ɉ���
	if (moveDir.x != 0.0f || moveDir.z != 0.0f) {
		acceleration += 0.1f;
	}
	else {
		acceleration -= 0.8f;
		if (acceleration < 0.0f) {
			acceleration = 0.0f;
		}
	}

	//���E���x�𒴂�����ړ����x�����E���x�ɐݒ�
	if (acceleration > speedLimit) {
		acceleration = speedLimit;
	}

	//�ړ����x���v�Z
	moveSpeed.x = dir.x * acceleration;
	moveSpeed.z = dir.z * acceleration;

	//�W�����v���łȂ���΃W�����v������
	if (pad->IsTrigger(pad->enButtonA) 
		&& !m_player->GetIsJump() 
		&& m_player->GetIsOnGround()) 
	{
		moveSpeed = Jump(moveSpeed);
	}

	return moveSpeed;
}

D3DXVECTOR3 PlayerMove::Jump(const D3DXVECTOR3& speed)
{
	D3DXVECTOR3 moveSpeed = speed;
	moveSpeed.y = 10.0f;

	m_player->SetIsJump();

	CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
	SE->Init("Assets/sound/U_Voice_1.wav");
	SE->Play(false);

	return moveSpeed;
}

void PlayerMove::Turn()
{
	m_rotationFrameCount++;
	//�ړ����Ă���Ȃ������ς���
	D3DXVECTOR3 playerDir = m_player->GetPlayerDir();
	D3DXVec3Normalize(&playerDir, &playerDir);
	D3DXVECTOR3 stickDir = dir;
	D3DXVec3Normalize(&stickDir, &stickDir);
	float angle = D3DXVec3Dot(&playerDir, &stickDir);
	if (angle < -1.0f)
	{
		angle = -1.0f;
	}
	if (angle > 1.0f)
	{
		angle = 1.0f;
	}
	angle = acosf(angle);
	D3DXVECTOR3 hoge;
	D3DXVec3Cross(&hoge, &playerDir, &stickDir);
	//�x�N�g����������������
	if (hoge.y < 0.0f) {
		angle *= -1.0f;
	}

	angle /= 5;
	D3DXQUATERNION rotation = m_player->GetRotation();

	if (m_rotationFrameCount <= 5) {
		D3DXQUATERNION rot;
		D3DXQuaternionIdentity(&rot);
		D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);
		D3DXQuaternionMultiply(&rotation, &rotation, &rot);
		m_rotationFrameCount = 0;
	}

	m_player->SetRotation(rotation);
}
