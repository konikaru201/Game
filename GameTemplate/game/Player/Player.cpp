#include "stdafx.h"
#include "Player.h"
#include "Scene/GameScene.h"
#include "myEngine/HID/Pad.h"
#include "myEngine/Graphics/ShadowMap.h"
#include "myEngine/Timer/Timer.h"

#define SPEED 8.0f

Player* g_player;

Player::Player()
{
}

Player::~Player()
{
}

bool Player::Start()
{
	//�X�y�L�����}�b�v�����[�h
	HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/utc_spec.tga",
		&specularMap
	);

	if (specularMap != NULL) {
		model.SetSpecularMap(specularMap);
	}

	//���f���f�[�^�����[�h���ď�����
	modelData.LoadModelData("Assets/modelData/Unity.x", &animation);
	model.Init(&modelData);
	//���C�g��ݒ�
	model.SetLight(&gameScene->GetLight());

	//���W�ƌ�����������
	position = { 0.0f,0.0f,0.0f };
	rotation = { 0.0f,0.0f,0.0f,1.0f };

	//�L�����N�^�[�R���g���[���[��������
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(0.3f, 1.0f);
	characterController.Init(coll, position);
	characterController.SetGravity(-20.0f);	//�d�͋���

	animation.PlayAnimation(AnimationStand, 0.3f);
	animation.SetAnimationEndTime(AnimationRun, 0.8f);
	animation.SetAnimationLoopflg(AnimationJump, false);

	return true;
}

void Player::Update()
{
	if (gameScene == nullptr) { return; }

	//�ړ����x��ݒ�
	D3DXVECTOR3 moveSpeed = Move();
	

	if (isOnWall == false && wallJump == false) {
		if (pad->GetLStickXF() != 0.0f || pad->GetLStickYF() != 0.0f) {
			//�ړ����Ă���Ȃ������ς���
			D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), atan2f(dir.x, dir.z));
			if (characterController.IsJump() == false) {
				currentAnim = AnimationRun;
			}
		}
		else {
			if (characterController.IsJump() == false) {
				currentAnim = AnimationStand;
			}
		}
	}
	

	//�ړ����̏ア��Ȃ�ړ����ɂ��Ă���
	if (characterController.IsOnMoveFloor() == true || characterController.IsOnMoveFloor2() == true)
	{
		if (g_moveFloor != nullptr && g_moveFloor2 != nullptr
			&& g_moveFloor->GetMoveFlag() == true
			|| g_moveFloor2->GetmoveFlg() == true) {
			D3DXVECTOR3 AddPos;
			if (characterController.IsOnMoveFloor() == true)
			{
				AddPos = g_moveFloor->GetMoveSpeed();
			}
			else
			{
				AddPos = g_moveFloor2->GetMoveSpeed();
			}
			moveSpeed += AddPos * 60.0f;
		}
	}

	//�W�����v�u���b�N�ɓ��������Ƃ�
	if (gameScene->GetMap()->GetJumpBlock() != nullptr 
		&& characterController.IsOnJumpBlock() == true)
	{
		D3DXVECTOR3 AddPos = gameScene->GetMap()->GetJumpBlock()->GetMoveSpeed();
		moveSpeed += AddPos;
	}

	////�n�ʏ�ɂ���Ȃ�
	//if (GetIsOnGround()) {
	//	isOnWall = false;
	//	wallJump = false;
	//}

	//�������玀�S�t���O�𗧂Ă�
	if (position.y <= -20.0f)
	{
		isDead = true;
		//g_shadowMap.SetPlayerDead(true);
		//�e�X�g�p
		//position = { 0.0f,0.0f,0.0f };
		//characterController.SetPosition(position);
	}

	//�A�j���[�V�������ς���Ă�����ύX
	if (currentAnim != prevAnim) {
		animation.PlayAnimation(currentAnim, 0.3f);
	}

	//�O�̃A�j���[�V������ۑ�
	prevAnim = currentAnim;

	//2�C3��ڂ̃W�����v�͈�莞�Ԍo�Ƃł��Ȃ�����
	//2��ڂ̃W�����v
	if (JumpCount == 1 && GetIsOnGround()) 
	{
		JumpFrameCount++;
		if (JumpFrameCount % 10 == 0) {
			JumpCount = 0;
			JumpFrameCount = 0;
		}
	}
	//3��ڂ̃W�����v
	else if (JumpCount == 2 && GetIsOnGround()) 
	{
		JumpFrameCount++;
		if (JumpFrameCount % 8 == 0) {
			JumpCount = 0;
			JumpFrameCount = 0;
		}
	}
	characterController.SetMoveSpeed(moveSpeed);
	//�L�����N�^�[�R���g���[���[�����s
	characterController.Execute();
	//���W��ݒ�
	position = characterController.GetPosition();
	//�A�j���[�V�����̍X�V
	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Player::Render()
{
	if (gameScene == nullptr) { return; }
	model.Draw(&gameScene->GetGameCamera()->GetViewMatrix(), &gameScene->GetGameCamera()->GetViewProjectionMatrix());
}

void Player::RenderShadow(D3DXMATRIX * viewMatrix, D3DXMATRIX * projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (g_player != nullptr && gameScene->GetGameCamera() != nullptr){
		model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		model.Draw(viewMatrix, projMatrix);
		model.SetDrawShadowMap(false, false);
	}
}

D3DXVECTOR3 Player::Move()
{
	//�ړ����x���擾
	D3DXVECTOR3 move = characterController.GetMoveSpeed();

	//�X�e�B�b�N�̓��͗ʂ��擾
	D3DXVECTOR3 moveDir;
	moveDir.y = 0.0f;
	moveDir.x = pad->GetLStickXF();
	moveDir.z = pad->GetLStickYF();

	//�J�����̋t�s����쐬
	D3DXMATRIX ViewMatrix = gameScene->GetGameCamera()->GetViewMatrix();
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

	//�ړ����x���v�Z
	move.x = dir.x * SPEED;
	move.z = dir.z * SPEED;

	//A�{�^���������ꂽ��W�����v
	if (pad->IsTrigger(pad->enButtonA)
		&& !characterController.IsJump()
		&& GetIsOnGround())
	{
		if (JumpCount == 0) {
			//move.y = 8.0f;
			move.y = 14.0f;
			JumpCount++;
		}
		//����Ȃ���2,3��ڂ̃W�����v���ł���
		else if (move.x != 0.0f || move.z != 0.0f) {
			if (JumpCount == 1) {
				move.y = 12.0f;
				JumpCount++;
			}
			else if (JumpCount == 2) {
				move.y = 16.0f;
				JumpCount = 0;
			}
		}
		characterController.Jump();
		currentAnim = AnimationJump;
	}

	////�ǂɓ���������
	//if (characterController.IsOnWall()) {
	//	isOnWall = true;
	//}

	////�ǂɓ������Ă����
	//if (isOnWall) {
	//	if (pad->IsTrigger(pad->enButtonA)) {
	//		wallJump = true;
	//		wallJumpExecute = true;
	//		isOnWall = false;
	//		//�v���C���[�̌������擾����
	//		playerDir = GetPlayerDir();
	//		playerDir = playerDir * 10.0f;
	//	}
	//	move.x = 0.0f;
	//	move.y = -0.2f;
	//	move.z = 0.0f;
	//}

	////�ǃW�����v��
	//if (wallJump) {
	//	//�ǂ̖@�����擾����
	//	D3DXVECTOR3 hitNormal = characterController.GethitNormal();
	//	D3DXVec3Normalize(&hitNormal, &hitNormal);
	//	
	//	//���˃x�N�g�������߂�
	//	D3DXVECTOR3 playerDirR = -playerDir;
	//	float dot = D3DXVec3Dot(&hitNormal, &playerDirR);
	//	hitNormal = hitNormal * dot * 2.0f;
	//	D3DXVECTOR3 R = playerDir + hitNormal;
	//	D3DXVec3Normalize(&R, &R);
	//	if (wallJumpExecute) {
	//		move.y = 8.0f;
	//		wallJumpExecute = false;
	//	}
	//	move.x = R.x * 8.0f;
	//	move.z = R.z * 8.0f;

	//	D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), atan2f(R.x, R.z));
	//}

	return move;
}

void Player::Reset()
{
	//���W�ƌ�����������
	position = { 0.0f,0.0f,0.0f };
	rotation = { 0.0f,0.0f,0.0f,1.0f };
	characterController.SetPosition(position);

	isDead = false;

	//�A�j���[�V�����̍X�V
	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}