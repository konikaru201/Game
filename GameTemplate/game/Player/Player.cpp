#include "stdafx.h"
#include "Player.h"
#include "Scene/SceneManager.h"
#include "myEngine/HID/Pad.h"
#include "myEngine/Graphics/ShadowMap.h"
#include "myEngine/Timer/Timer.h"
#include "Map/Map.h"

Player* player;

Player::Player() :
	m_playerStateMachine(this)
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

	animation.PlayAnimation(IPlayerState::AnimationStand, 0.3f);
	animation.SetAnimationEndTime(IPlayerState::AnimationRun, 0.8f);
	animation.SetAnimationEndTime(IPlayerState::AnimationJump, 1.1f);
	animation.SetAnimationLoopflg(IPlayerState::AnimationJump, false);
	animation.SetAnimationLoopflg(IPlayerState::AnimationPose, false);
	animation.SetAnimationLoopflg(IPlayerState::AnimationDead, false);
	
	//�e��`�悷��t���O�𗧂Ă�
	SetRenderToShadow();

	//�X�e�[�g�}�V�����Q�[���I�u�W�F�N�g�ɒǉ�
	goMgr->AddGameObject(&m_playerStateMachine);

	return true;
}

void Player::Update()
{
	if (sceneManager->GetChangeSceneFlag()) {
		//��ԃN���X�̎��S�t���O�𗧂Ă�
		m_playerStateMachine.SetIsChangeState(true);
		m_playerStateMachine.Release();

		return;
	}

	if (position.y <= -20.0f) {
		m_fallPlayer = true;
	}

	//�o�l�ɓ��������Ƃ��W�����v
	if (m_treadOnSpring) {
		moveSpeed.y = 0.0f;
		moveSpeed.y += jumpSpeed * 2;
		playerController.Jump();
		animation.PlayAnimation(IPlayerState::AnimationNo::AnimationJump);
		m_treadOnSpring = false;
	}

	//�G�𓥂񂾂�W�����v
	if (m_treadOnEnemy) {
		moveSpeed.y = 0.0f;
		moveSpeed.y += jumpSpeed;
		playerController.Jump();
		animation.PlayAnimation(IPlayerState::AnimationNo::AnimationJump);
		m_treadOnEnemy = false;
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
	else if (playerController.IsOnMoveFloor2()) {
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

	//�A�j���[�V�������ς���Ă�����ύX
	if (m_currentAnim != m_prevAnim) {
		animation.PlayAnimation(m_currentAnim, 0.3f);
	}
	
	//�O�̃A�j���[�V�������X�V
	m_prevAnim = m_currentAnim;

	//�A�j���[�V�����̍X�V
	animation.Update(1.0f / 60.0f);

	//���[���h�s����X�V
	model.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Player::Render()
{
	model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

void Player::RenderShadow(D3DXMATRIX * viewMatrix, D3DXMATRIX * projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (player != nullptr && gameCamera != nullptr){
		model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		model.Draw(viewMatrix, projMatrix);
		model.SetDrawShadowMap(false, false);
	}
}

void Player::SilhouetteRender(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix)
{
	if (player != nullptr && gameCamera != nullptr) {
		model.SetSilhouetteRender(true);
		model.Draw(viewMatrix, projMatrix);
		model.SetSilhouetteRender(false);
	}
}