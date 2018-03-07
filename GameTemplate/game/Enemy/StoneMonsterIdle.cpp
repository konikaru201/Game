#include "stdafx.h"
#include "StoneMonsterIdle.h"
#include "StoneMonster.h"
#include "Player/Player.h"
#include "myEngine/Timer/Timer.h"
#include <time.h>
#include <stdlib.h>

void StoneMonsterIdle::Update()
{
	//���܂�Ă����瓮���Ȃ�
	if (m_stoneMonster->GetIsStepOn()) {
		D3DXVECTOR3 moveSpeed = m_stoneMonster->GetMoveSpeed();
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
		m_stoneMonster->SetMoveSpeed(moveSpeed);

		return;
	}

	//�v���C���[��T��
	Search();

	//�ړ�
	Move();

	//�ړ����n�߂���
	if (isMove) {
		if (m_stoneMonster->GetIsOnMoveFloor() || m_stoneMonster->GetIsOnMoveFloor2()) {
			TurnOnMoveFloor();
		}
		else {
			//��]
			Turn();
		}
	}

	//�������Ă�����
	if (GetIsFind()){
		m_sms->ChangeState(StoneMonsterState::enState_Follow);
		SetIsFind(false);
	}
}

bool StoneMonsterIdle::Start()
{
	//��x���������̎������������
	srand((unsigned)time(NULL));

	m_destination = m_stoneMonster->GetPosition();
	m_initPosition = m_stoneMonster->GetPosition();

	timer = 0.0f;
	isMove = false;

	return true;
}

void StoneMonsterIdle::Move()
{
	m_moveSpeed = m_stoneMonster->GetMoveSpeed();

	//���W���擾
	D3DXVECTOR3 position = m_stoneMonster->GetPosition();
	//�ړ���܂ł̋������v�Z
	D3DXVECTOR3 toDestination = m_destination - position;
	float length = D3DXVec3Length(&toDestination);
	//�ړ���Ƃ̋������߂�
	if (length <= 0.6f) {
		timer += Timer::GetFrameDeltaTime();
		if (timer >= 2.0f) {
			//�����_���Ɉړ��������
			//0.0�`1.0�̒l�ɕϊ�
			float randomPositionX;
			float randomPositionZ;
			randomPositionX = (float)rand() / 32767.0;
			randomPositionZ = (float)rand() / 32767.0;
			//0.0�`6.0�̒l�ɕϊ�
			randomPositionX *= 6.0f;
			randomPositionZ *= 6.0f;
			//-3.0�`3.0�̒l�ɕϊ�
			randomPositionX -= 3.0f;
			randomPositionZ -= 3.0f;
			//�ړ���̍��W���v�Z
			D3DXVECTOR3 toRandomPosition;
			toRandomPosition.x = m_initPosition.x + randomPositionX;
			toRandomPosition.y = 0.0f;
			toRandomPosition.z = m_initPosition.z + randomPositionZ;

			//�ړ���̍��W��ۑ�
			m_destination.x = m_initPosition.x + randomPositionX;
			m_destination.y = m_initPosition.y;
			m_destination.z = m_initPosition.z + randomPositionZ;

			//�ړ����x���v�Z
			D3DXVec3Normalize(&toRandomPosition, &toRandomPosition);
			toRandomPosition *= m_speed;
			m_moveSpeed.x = toRandomPosition.x;
			m_moveSpeed.z = toRandomPosition.z;
			//�^�C�}�[��������
			timer = 0.0f;
			isMove = true;
		}
		else {
			//�����Ȃ�
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;
		}
	}
	else {
		//�ǂ������ď������W���痣�ꂽ��߂�
		if (length >= 10.0f) {
			toDestination = m_initPosition - position;
			D3DXVec3Normalize(&toDestination, &toDestination);
			toDestination *= m_speed;
			m_moveSpeed.x = toDestination.x;
			m_moveSpeed.z = toDestination.z;
		}
		else {
			//�ړ���ɐi��
			D3DXVec3Normalize(&toDestination, &toDestination);
			toDestination *= m_speed;
			m_moveSpeed.x = toDestination.x;
			m_moveSpeed.z = toDestination.z;
			timer += Timer::GetFrameDeltaTime();
			//�R�ۂŋl�܂��Ă�����ړ���������ʒu�ɖ߂�
			if (timer >= 7.0f) {
				m_destination = m_initPosition;
				timer = 0.0f;
			}
		}
	}

	//�ړ����̏�Ȃ瓮���Ȃ�
	if (m_stoneMonster->GetIsOnMoveFloor() || m_stoneMonster->GetIsOnMoveFloor2())
	{
		D3DXVECTOR3 toMoveFloorPosition;
		if (m_stoneMonster->GetIsOnMoveFloor()) {
			toMoveFloorPosition = m_stoneMonster->GetMoveFloorPosition() - position;
		}
		else {
			toMoveFloorPosition = m_stoneMonster->GetMoveFloor2Position() - position;
		}
		float length = D3DXVec3Length(&toMoveFloorPosition);
		if (length >= 2.0f) {
			D3DXVec3Normalize(&toMoveFloorPosition, &toMoveFloorPosition);
			toMoveFloorPosition *= m_speed;
			m_moveSpeed.x = toMoveFloorPosition.x;
			m_moveSpeed.z = toMoveFloorPosition.z;
		}
		else {
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = 0.0f;
		}
	}

	m_stoneMonster->SetMoveSpeed(m_moveSpeed);
}

void StoneMonsterIdle::Search()
{
	//�v���C���[�̍��W���擾
	D3DXVECTOR3 playerPos = player->GetPosition();
	//���g����v���C���[�̃x�N�g�����v�Z
	D3DXVECTOR3 toPlayerDir = playerPos - m_stoneMonster->GetPosition();
	//�v���C���[�Ƃ̋������v�Z
	float length = D3DXVec3Length(&toPlayerDir);
	toPlayerDir.y = 0.0f;
	//���g����v���C���[�ւ̊p�x���v�Z
	D3DXVec3Normalize(&toPlayerDir, &toPlayerDir);
	D3DXVECTOR3 forward = m_stoneMonster->GetDirection();
	float angle = D3DXVec3Dot(&toPlayerDir, &forward);
	angle = acosf(angle);

	if (fabsf(angle) < D3DXToRadian(30.0f) && length < 8.0f || length < 5.0f)
	{
		//�������ꂽ
		SetIsFind(true);
	}
}

void StoneMonsterIdle::Turn()
{
	D3DXQUATERNION rot;
	D3DXQuaternionIdentity(&rot);
	m_rotationFrameCount++;
	//���f���̑O�������擾
	D3DXVECTOR3 forward = m_stoneMonster->GetDirection();
	D3DXVec3Normalize(&forward, &forward);
	//���W���擾
	D3DXVECTOR3 position = m_stoneMonster->GetPosition();
	//�ړ���ւ̃x�N�g�����v�Z
	D3DXVECTOR3 toDestination = m_destination - position;
	toDestination.y = 0.0f;
	D3DXVec3Normalize(&toDestination, &toDestination);
	float angle = D3DXVec3Dot(&forward, &toDestination);
	if (angle < -1.0f) {
		angle = -1.0f;
	}
	if (angle > 1.0f)
	{
		angle = 1.0f;
	}
	angle = acosf(angle);
	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &forward, &toDestination);
	if (Cross.y < 0.0f) {
		angle *= -1.0f;
	}
	angle /= 3;
	if (m_rotationFrameCount <= 3) {
		D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);
		D3DXQUATERNION rotation = m_stoneMonster->GetRotation();
		D3DXQuaternionMultiply(&rotation, &rotation, &rot);
		m_stoneMonster->SetRotation(rotation);
	}
	else {
		m_rotationFrameCount = 0;
	}
}

void StoneMonsterIdle::TurnOnMoveFloor()
{
	D3DXQUATERNION rot;
	D3DXQuaternionIdentity(&rot);
	m_rotationFrameCount++;
	//���f���̑O�������擾
	D3DXVECTOR3 forward = m_stoneMonster->GetDirection();
	D3DXVec3Normalize(&forward, &forward);
	
	m_turnCount++;
	if (m_turnCount % 300 == 0) {
		moveDirection.z *= -1.0f;
		m_turnCount = 0;
	}

	float angle = D3DXVec3Dot(&forward, &moveDirection);
	if (angle < -1.0f) {
		angle = -1.0f;
	}
	if (angle > 1.0f)
	{
		angle = 1.0f;
	}
	angle = acosf(angle);
	D3DXVECTOR3 Cross;
	D3DXVec3Cross(&Cross, &forward, &moveDirection);
	if (Cross.y < 0.0f) {
		angle *= -1.0f;
	}
	angle /= 5;
	if (m_rotationFrameCount <= 5) {
		D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);
		D3DXQUATERNION rotation = m_stoneMonster->GetRotation();
		D3DXQuaternionMultiply(&rotation, &rotation, &rot);
		m_stoneMonster->SetRotation(rotation);
	}
	else {
		m_rotationFrameCount = 0;
	}
}
