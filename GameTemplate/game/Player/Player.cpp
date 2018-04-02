#include "stdafx.h"
#include "Player.h"
#include "Scene/GameScene.h"
#include "myEngine/HID/Pad.h"
#include "myEngine/Graphics/ShadowMap.h"
#include "myEngine/Timer/Timer.h"
#include "Map/Map.h"

Player* player;

Player::Player()
{
}

Player::~Player()
{
	//���̂��폜
	playerController.RemoveRigidBoby();
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
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.6f, 0.6f, 0.6f, 1.0f));
	model.SetLight(&light);

	//���W�ƌ�����������
	position = { 0.0f,0.0f,15.0f };
	rotation = { 0.0f,0.0f,0.0f,1.0f };
	D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(180.0f));

	state = State_Walk;

	//�e�̃��[���h�s�񂩂�t�s��𐶐�
	D3DXMATRIX parentWorldMatrixInv;
	D3DXMatrixInverse(&parentWorldMatrixInv, 0, &parentWorldMatrix);
	D3DXVec3TransformCoord(&childPosition, &position, &parentWorldMatrixInv);
	
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
	animation.SetAnimationLoopflg(AnimationDead, false);
	
	//�e��`�悷��t���O�𗧂Ă�
	SetRenderToShadow();

	return true;
}

void Player::Update()
{
	D3DXQUATERNION rot;
	D3DXQuaternionIdentity(&rot);

	switch (state)
	{
		//�ړ���
	case State_Walk:
		if (!gameCamera->GetCameraReset()) 
		{
			moveSpeed = Move();

			if (getStar == false && (pad->GetLStickXF() != 0.0f || pad->GetLStickYF() != 0.0f))
			{
				m_rotationFrameCount++;
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

				angle /= 5;
				if (m_rotationFrameCount <= 5) {
					D3DXQuaternionRotationAxis(&rot, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), angle);
					D3DXQuaternionMultiply(&rotation, &rotation, &rot);
					m_rotationFrameCount = 0;
				}

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

		//�G�𓥂񂾂�W�����v
		if (m_treadOnEnemy) {
			moveSpeed.y = 0.0f;
			moveSpeed.y += jumpSpeed;
			playerController.Jump();
			animation.PlayAnimation(AnimationJump);
			currentAnim = AnimationJump;
			m_treadOnEnemy = false;
		}

		//�������疔�͓G�ɓ��������玀�S
		if (position.y < -20.0f || m_hitEnemy) {
			if (m_hitEnemy) {
				currentAnim = AnimationDead;
				moveSpeed.y = -9.8f;
			}
			state = State_Dead;

			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/U_Voice_2.wav");
			SE->Play(false);
		}

		//�X�^�[�l��������N���A
		if (getStar){
			moveSpeed.x = 0.0f;
			moveSpeed.z = 0.0f;
			if (GetIsOnGround()) {
				state = State_GetStar;

				CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
				SE->Init("Assets/sound/U_Voice_3.wav");
				SE->Play(false);
			}
		}
		
		//����
		if (m_moveFloorInertia) {
			m_ineltiaTime += Timer::GetFrameDeltaTime();
			//��C��R�ŏ��������̑��x�����炷
			m_airResistance = m_moveFloorSpeed * 60.0f;
			D3DXVec3Normalize(&m_airResistance, &m_airResistance);
			m_airResistance *= m_ineltiaTime;
			m_moveFloorSpeed *= 60.0f;
			moveSpeed += m_moveFloorSpeed - m_airResistance;
		}
		else if (m_moveFloor2Inertia) {
			m_ineltiaTime += Timer::GetFrameDeltaTime();
			//��C��R�ŏ��������̑��x�����炷
			m_airResistance = m_moveFloor2Speed * 60.0f;
			D3DXVec3Normalize(&m_airResistance, &m_airResistance);
			m_airResistance *= m_ineltiaTime;
			m_moveFloor2Speed *= 60.0f;
			moveSpeed += m_moveFloor2Speed - m_airResistance;
		}
		if (GetIsOnGround())
		{
			m_moveFloorInertia = false;
			m_moveFloor2Inertia = false;
			m_ineltiaTime = 0.0f;
		}

		//��ԋ߂��̈ړ����̃��[���h�s����擾
		if (map != nullptr && map->GetIsMoveFloor()) {
			if (!map->GetMoveFloorList().empty()) {
				moveFloorWorldMatrix = map->MoveFloorWorldMatrix(position);
			}
		}
		if (map != nullptr && map->GetIsMoveFloor2()) {
			if (!map->GetMoveFloor2List().empty()) {
				moveFloor2WorldMatrix = map->MoveFloor2WorldMatrix(position);
			}
		}
		//�ړ����ɓ�����������Ă���
		if (playerController.IsOnMoveFloor()) {
			if (parentFirstHit) {
				//�e���猩���v���C���[�̍��W���X�V
				D3DXMATRIX moveFloorWorldMatrixInv;
				D3DXMatrixInverse(&moveFloorWorldMatrixInv, NULL, &moveFloorWorldMatrix);
				D3DXVec3TransformCoord(&moveFloorChildPosition, &position, &moveFloorWorldMatrixInv);
				parentFirstHit = false;
			}
			//�v���C���[�̃��[���h���W�ɕϊ�����
			D3DXVec3TransformCoord(&position, &moveFloorChildPosition, &moveFloorWorldMatrix);
			playerController.SetPosition(position);

			if (playerController.IsJump()) {
				m_moveFloorInertia = true;
			}

			playerController.SetMoveSpeed(moveSpeed);
			//�L�����N�^�[�R���g���[���[�����s
			playerController.Execute();
			//���W��ݒ�
			position = playerController.GetPosition();
			//�e���猩���v���C���[�̍��W���X�V
			D3DXMATRIX moveFloorWorldMatrixInv;
			D3DXMatrixInverse(&moveFloorWorldMatrixInv, NULL, &moveFloorWorldMatrix);
			D3DXVec3TransformCoord(&moveFloorChildPosition, &position, &moveFloorWorldMatrixInv);
		}
		else if(playerController.IsOnMoveFloor2()) {
			if (secondParentFirstHit) {
				//�e���猩���v���C���[�̍��W���X�V
				D3DXMATRIX moveFloor2WorldMatrixInv;
				D3DXMatrixInverse(&moveFloor2WorldMatrixInv, NULL, &moveFloor2WorldMatrix);
				D3DXVec3TransformCoord(&moveFloor2ChildPosition, &position, &moveFloor2WorldMatrixInv);
				secondParentFirstHit = false;
			}
			//�v���C���[�̃��[���h���W�ɕϊ�����
			D3DXVec3TransformCoord(&position, &moveFloor2ChildPosition, &moveFloor2WorldMatrix);
			playerController.SetPosition(position);

			if (playerController.IsJump()) {
				m_moveFloor2Inertia = true;
			}

			playerController.SetMoveSpeed(moveSpeed);
			//�L�����N�^�[�R���g���[���[�����s
			playerController.Execute();
			//���W��ݒ�
			position = playerController.GetPosition();
			//�e���猩���v���C���[�̍��W���X�V
			D3DXMATRIX moveFloor2WorldMatrixInv;
			D3DXMatrixInverse(&moveFloor2WorldMatrixInv, NULL, &moveFloor2WorldMatrix);
			D3DXVec3TransformCoord(&moveFloor2ChildPosition, &position, &moveFloor2WorldMatrixInv);
		}
		//�u���b�N�ɓ���������
		else if (playerController.IsOnBlock() == true)
		{
			if (parentFirstHit) {
				//�e�̃��[���h�s�񂩂�t�s��𐶐�
				D3DXMATRIX parentWorldMatrixInv;
				D3DXMatrixInverse(&parentWorldMatrixInv, NULL, &parentWorldMatrix);
				D3DXVec3TransformCoord(&childPosition, &position, &parentWorldMatrixInv);
				parentFirstHit = false;
			}

			//�v���C���[�̃��[���h���W�ɕϊ�����
			D3DXVec3TransformCoord(&position, &childPosition, &parentWorldMatrix);
			playerController.SetPosition(position);

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
	model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetViewProjectionMatrix());
}

void Player::RenderShadow(D3DXMATRIX * viewMatrix, D3DXMATRIX * projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (player != nullptr && gameCamera != nullptr){
		model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		model.Draw(viewMatrix, projMatrix);
		model.SetDrawShadowMap(false, false);
	}
}

void Player::DepthStencilRender(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix)
{
	if (player != nullptr && gameCamera != nullptr) {
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
		&& GetIsOnGround())
	{
		move.y = 10.0f;

		playerController.Jump();

		animation.PlayAnimation(AnimationJump);
		currentAnim = AnimationJump;
		CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
		SE->Init("Assets/sound/U_Voice_1.wav");
		SE->Play(false);
	}
	return move;
}