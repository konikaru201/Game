#include "stdafx.h"
#include "Player.h"
#include "Scene/GameScene.h"
#include "myEngine/HID/Pad.h"
#include "myEngine/Graphics/ShadowMap.h"
#include "myEngine/Timer/Timer.h"

Player* g_player;

Player::Player()
{
}

Player::~Player()
{
	//�e�N�X�`���̊J��
	if (specularMap != NULL) {
		specularMap->Release();
	}
	if (normalMap != NULL) {
		normalMap->Release();
	}
}

bool Player::Start()
{
	//�X�y�L�����}�b�v�����[�h
	HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/utc_spec.tga",
		&specularMap
	);
	//D3DXCreateTextureFromFileA�̖߂�l���`�F�b�N
	if (FAILED(hr)) {
		MessageBox(NULL, "�e�N�X�`���̃��[�h�Ɏ��s���܂����B�X�y�L�����}�b�v", "�G���[", MB_OK);
	}
	if (specularMap != NULL) {
		model.SetSpecularMap(specularMap);
	}

	//�@���}�b�v�����[�h
	hr = D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/utc_normal.tga",
		&normalMap
	);
	//D3DXCreateTextureFromFileA�̖߂�l���`�F�b�N
	if (FAILED(hr)) {
		MessageBox(NULL, "�e�N�X�`���̃��[�h�Ɏ��s���܂����B�@���}�b�v", "�G���[", MB_OK);
	}
	if (normalMap != NULL) {
		model.SetNormalMap(normalMap);
	}

	//���f���f�[�^�����[�h���ď�����
	modelData.LoadModelData("Assets/modelData/Unity.x", &animation);
	model.Init(&modelData);
	//���C�g��ݒ�
	model.SetLight(&gameScene->GetLight());

	if (gameScene->GetStateStage() == 0) {
		//���W�ƌ�����������
		position = { 0.0f,0.0f,0.0f };
		rotation = { 0.0f,0.0f,0.0f,1.0f };
	}
	else if(gameScene->GetStateStage() == 1) {
		//���W�ƌ�����������
		position = { 0.0f,2.5f,0.0f };
		rotation = { 0.0f,0.0f,0.0f,1.0f };
	}

	state = State_Move;

	//�e�̃��[���h�s�񂩂�t�s��𐶐�
	D3DXMATRIX parentWorldMatrixInv;
	D3DXMatrixInverse(&parentWorldMatrixInv, 0, &parentWorldMatrix);
	D3DXVec3TransformCoord(&childPosition, &position, &parentWorldMatrixInv);
	////�e�̉�]�s�񂩂�t�N�H�[�^�j�I���𐶐�
	//D3DXQUATERNION parentRotationInv;
	//D3DXQuaternionRotationMatrix(&parentRotationInv, &parentRotationMatrix);
	//D3DXQuaternionInverse(&parentRotationInv, &parentRotationInv);
	//D3DXQuaternionMultiply(&childRotation, &rotation, &parentRotationInv);
	
	D3DXMATRIX secondParentWorldMatrixInv;
	D3DXMatrixInverse(&secondParentWorldMatrixInv, 0, &secondParentWorldMatrix);
	D3DXVec3TransformCoord(&secondChildPosition, &position, &secondParentWorldMatrixInv);

	//�L�����N�^�[�R���g���[���[��������
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(0.3f, 1.0f);
	playerController.Init(coll, position);
	playerController.SetGravity(-20.0f);	//�d�͋���

	animation.PlayAnimation(AnimationStand, 0.3f);
	animation.SetAnimationEndTime(AnimationRun, 0.8f);
	animation.SetAnimationEndTime(AnimationJump, 1.1f);
	animation.SetAnimationLoopflg(AnimationJump, false);
	animation.SetAnimationLoopflg(AnimationPose, false);
	
	return true;
}

void Player::Update()
{
	if (gameScene == nullptr) { return; }

	//�X�e�[�W�؂�ւ����Ƀv���C���[���폜����̂ō��̂��폜
	if (gameScene->GetChengeStage()) {
		playerController.RemoveRigidBoby();
	}

	moveSpeed = Move();

	D3DXQUATERNION rot;
	D3DXQuaternionIdentity(&rot);
	switch (state)
	{
		//�ړ���
	case State_Move:
		if (pad->GetLStickXF() != 0.0f || pad->GetLStickYF() != 0.0f)
		{
			//�ړ����Ă���Ȃ������ς���
			D3DXVECTOR3 playerDir = GetPlayerDir();
			D3DXVec3Normalize(&playerDir, &playerDir);
			D3DXVECTOR3 stickDir = dir;
			D3DXVec3Normalize(&stickDir, &stickDir);
			angle = D3DXVec3Dot(&playerDir, &stickDir);
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
			D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);
			D3DXQuaternionMultiply(&rotation, &rotation, &rot);

			if (!(playerController.IsJump())) {
				currentAnim = AnimationRun;

				timer += Timer::GetFrameDeltaTime();

				if (timer >= 0.4f) {
					CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
					SE->Init("Assets/sound/FootStep.wav");
					SE->Play(false);
					timer = 0.0f;
				}
			}	
		}
		else {
			if (!(playerController.IsJump())) {
				currentAnim = AnimationStand;
			}
		}

		//�ړ����̏ア��Ȃ�ړ����ɂ��Ă���
		if (playerController.IsOnMoveFloor() || playerController.IsOnMoveFloor2())
		{
			if (g_moveFloor != nullptr && g_moveFloor2 != nullptr
				&& g_moveFloor->GetMoveFlag()
				|| g_moveFloor2->GetmoveFlg()) {
				D3DXVECTOR3 AddPos;
				if (playerController.IsOnMoveFloor())
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

		//�X�v�����O�ɓ��������Ƃ��W�����v
		if (m_treadOnSpring) {
			moveSpeed.y = 0.0f;
			moveSpeed.y += jumpSpeed * 2;
			playerController.Jump();
			animation.PlayAnimation(AnimationJump);
			currentAnim = AnimationJump;
			m_treadOnSpring = false;
		}

		//�G�ɓ��������Ƃ��W�����v
		if (m_treadOnEnemy) {
			moveSpeed.y = 0.0f;
			moveSpeed.y += jumpSpeed;
			playerController.Jump();
			currentAnim = AnimationJump;
			m_treadOnEnemy = false;
		}

		//�������疔�͓G�ɓ��������玀�S
		if (position.y < -20.0f || m_hitEnemy) {
			state = State_Dead;
			m_hitEnemy = false;

			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/U_Voice_2.wav");
			SE->Play(false);
		}

		//�X�^�[�l��������N���A
		if (getStar && GetIsOnGround()) {
			state = State_GetStar;

			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/U_Voice_3.wav");
			SE->Play(false);
		}

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
		
		//�u���b�N�ɓ���������
		if (playerController.IsOnBlock() == true)
		{
			if (parentFirstHit) {
				//�e�̃��[���h�s�񂩂�t�s��𐶐�
				D3DXMATRIX parentWorldMatrixInv;
				D3DXMatrixInverse(&parentWorldMatrixInv, NULL, &parentWorldMatrix);
				D3DXVec3TransformCoord(&childPosition, &position, &parentWorldMatrixInv);
				////�e�̉�]�s�񂩂�t�N�H�[�^�j�I���𐶐�
				//D3DXQUATERNION parentRotationInv;
				//D3DXQuaternionRotationMatrix(&parentRotationInv, &parentRotationMatrix);
				//D3DXQuaternionInverse(&parentRotationInv, &parentRotationInv);
				//D3DXQuaternionMultiply(&childRotation, &rotation, &parentRotationInv);
				parentFirstHit = false;
			}

			//�v���C���[�̃��[���h���W�ɕϊ�����
			D3DXVec3TransformCoord(&position, &childPosition, &parentWorldMatrix);
			playerController.SetPosition(position);

			////�e���猩���v���C���[����]������
			//D3DXQuaternionMultiply(&childRotation, &childRotation, &rot);
			////�v���C���[�̉�]�ɕϊ�����
			//D3DXQUATERNION parentRotation;
			//D3DXQuaternionRotationMatrix(&parentRotation, &parentRotationMatrix);
			//D3DXQuaternionMultiply(&rotation, &childRotation, &parentRotation);

			//�v���C���[�̈ړ����x��ݒ�
			playerController.SetMoveSpeed(moveSpeed);
			//�L�����N�^�[�R���g���[���[�����s
			playerController.Execute();
			//���W��ݒ�
			position = playerController.GetPosition();

			//�e���猩���v���C���[�̍��W���X�V
			D3DXMATRIX worldMatrixInv;
			D3DXMatrixInverse(&worldMatrixInv, NULL, &parentWorldMatrix);
			D3DXVec3TransformCoord(&childPosition, &position, &worldMatrixInv);

			////�e���猩���v���C���[�̉�]���X�V
			//D3DXQUATERNION parentRotationInv;
			//D3DXQuaternionRotationMatrix(&parentRotationInv, &parentRotationMatrix);
			//D3DXQuaternionInverse(&parentRotationInv, &parentRotationInv);
			//D3DXQuaternionMultiply(&childRotation, &rotation, &parentRotationInv);
		}
		//�u���b�N2�ɓ���������
		else if (playerController.IsOnBlock2() == true)
		{
			if (secondParentFirstHit) {
				//�e�̃��[���h�s�񂩂�t�s��𐶐�
				D3DXMATRIX secondParentWorldMatrixInv;
				D3DXMatrixInverse(&secondParentWorldMatrixInv, NULL, &secondParentWorldMatrix);
				D3DXVec3TransformCoord(&secondChildPosition, &position, &secondParentWorldMatrixInv);
				secondParentFirstHit = false;
			}

			//�v���C���[�̃��[���h���W�ɕϊ�����
			D3DXVec3TransformCoord(&position, &secondChildPosition, &secondParentWorldMatrix);
			playerController.SetPosition(position);
			//�v���C���[�̈ړ����x��ݒ�
			playerController.SetMoveSpeed(moveSpeed);
			//�L�����N�^�[�R���g���[���[�����s
			playerController.Execute();
			//���W��ݒ�
			position = playerController.GetPosition();

			//�e���猩���v���C���[�̍��W���X�V
			D3DXMATRIX worldMatrixInv;
			D3DXMatrixInverse(&worldMatrixInv, NULL, &secondParentWorldMatrix);
			D3DXVec3TransformCoord(&secondChildPosition, &position, &worldMatrixInv);
		}
		else {
			//�v���C���[�̈ړ����x��ݒ�
			playerController.SetMoveSpeed(moveSpeed);
			//�L�����N�^�[�R���g���[���[�����s
			playerController.Execute();
			//���W��ݒ�
			position = playerController.GetPosition();
			parentFirstHit = true;
			secondParentFirstHit = true;
		}

		break;

		//���S��
	case State_Dead:
		//g_shadowMap.SetPlayerDead(true);
		//�e�X�g�p
		//position = { 0.0f,2.5f,0.0f };
		//playerController.SetPosition(position);
		//D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), atan2f(dir.x, dir.z));
		//state = State_Move;
		
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
		//�v���C���[�̈ړ����x��ݒ�
		playerController.SetMoveSpeed(moveSpeed);
		//�L�����N�^�[�R���g���[���[�����s
		playerController.Execute();
		//���W��ݒ�
		position = playerController.GetPosition();

		timer += Timer::GetFrameDeltaTime();
		if (timer >= 2.0f) {
			m_playerDead = true;
		}
		break;

		//�X�^�[�l����
	case State_GetStar:
		currentAnim = AnimationPose;
		if (!animation.IsPlay()) {
			animationEnd = true;
		}
		break;
	}

	//�A�j���[�V�������ς���Ă�����ύX
	if (currentAnim != prevAnim) {
		animation.PlayAnimation(currentAnim, 0.3f);
	}

	//�O�̃A�j���[�V������ۑ�
	prevAnim = currentAnim;

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

void Player::DepthStencilRender(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix)
{
	if (g_player != nullptr && gameScene->GetGameCamera() != nullptr) {
		model.SetDepthStencilRender(true);
		model.Draw(viewMatrix, projMatrix);
		model.SetDepthStencilRender(false);
	}
}

D3DXVECTOR3 Player::Move()
{
	//�ړ����x���擾
	D3DXVECTOR3 move = playerController.GetMoveSpeed();

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

	//�ړ����Ă�Ȃ珙�X�ɉ���
	if (moveDir.x != 0.0f || moveDir.z != 0.0f) {
		acceleration += 0.1f;
	}
	else {
		acceleration -= 0.5f;
		if (acceleration < 0.0f) {
			acceleration = 0.0f;
		}
	}

	//���E���x�𒴂�����ړ����x�����E���x�ɐݒ�
	if (acceleration > speedLimit) {
		acceleration = speedLimit;
	}

	//������90�x�ȏ�ς�����瑬�x��������
	if (currentDir.x != 0.0f || currentDir.y != 0.0f || currentDir.z != 0.0f){
		if (D3DXVec3Dot(&currentDir, &dir) < -0.1f) {
			acceleration = 1.0f;
		}
	}
	//1�t���[���O�̌�����ۑ�
	currentDir = dir;

	//�ړ����x���v�Z
	move.x = dir.x * acceleration;
	move.z = dir.z * acceleration;

	//A�{�^���������ꂽ��W�����v
	if (pad->IsTrigger(pad->enButtonA)
		&& !playerController.IsJump()
		/*&& GetIsOnGround()*/)
	{
		if (JumpCount == 0) {
			move.y = 12.0f;
			JumpCount++;
		}
		//����Ȃ���2,3��ڂ̃W�����v���ł���
		else if (move.x != 0.0f || move.z != 0.0f) {
			if (JumpCount == 1) {
				move.y = 15.0f;
				JumpCount++;
			}
			else if (JumpCount == 2) {
				move.y = 18.0f;
				JumpCount = 0;
			}
		}
		playerController.Jump();
		currentAnim = AnimationJump;

		CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
		SE->Init("Assets/sound/U_Voice_1.wav");
		SE->Play(false);
	}

	////�ǂɓ���������
	//if (playerController.IsOnWall()) {
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
	//	D3DXVECTOR3 hitNormal = playerController.GethitNormal();
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
	position = { 0.0f,2.5f,0.0f };
	D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), atan2f(dir.x, dir.z));
	playerController.SetPosition(position);

	//�A�j���[�V�����̍X�V
	animation.Update(1.0f / 60.0f);
	model.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}