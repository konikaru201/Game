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
	m_playerController.RemoveRigidBoby();
	//�e�N�X�`���̊J��
	if (m_specularMap != NULL) {
		m_specularMap->Release();
	}
	if (m_normalMap != NULL) {
		m_normalMap->Release();
	}
}

bool Player::Start()
{
	//�X�y�L�����}�b�v�����[�h
	HRESULT hr = D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/utc_spec.tga",
		&m_specularMap
	);
	//D3DXCreateTextureFromFileA�̖߂�l���`�F�b�N
	if (FAILED(hr)) {
		MessageBox(NULL, "�e�N�X�`���̃��[�h�Ɏ��s���܂����B�X�y�L�����}�b�v", "�G���[", MB_OK);
	}
	if (m_specularMap != NULL) {
		m_model.SetSpecularMap(m_specularMap);
	}

	//�@���}�b�v�����[�h
	hr = D3DXCreateTextureFromFileA(g_pd3dDevice,
		"Assets/modelData/utc_normal.tga",
		&m_normalMap
	);
	//D3DXCreateTextureFromFileA�̖߂�l���`�F�b�N
	if (FAILED(hr)) {
		MessageBox(NULL, "�e�N�X�`���̃��[�h�Ɏ��s���܂����B�@���}�b�v", "�G���[", MB_OK);
	}
	if (m_normalMap != NULL) {
		m_model.SetNormalMap(m_normalMap);
	}

	//���f���f�[�^�����[�h���ď�����
	m_modelData.LoadModelData("Assets/modelData/Unity.x", &m_animation);
	m_model.Init(&m_modelData);
	//���C�g��ݒ�
	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetAmbientLight(D3DXVECTOR4(0.6f, 0.6f, 0.6f, 1.0f));
	m_model.SetLight(&m_light);

	//���W�ƌ�����������
	m_position = { 0.0f,0.0f,15.0f };
	m_rotation = { 0.0f,0.0f,0.0f,1.0f };
	D3DXQuaternionRotationAxis(&m_rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(180.0f));

	//�e�̃��[���h�s�񂩂�t�s��𐶐�
	D3DXMATRIX parentWorldMatrixInv;
	D3DXMatrixInverse(&parentWorldMatrixInv, 0, &m_parentWorldMatrix);
	D3DXVec3TransformCoord(&m_childPosition, &m_position, &parentWorldMatrixInv);
	
	D3DXMATRIX secondParentWorldMatrixInv;
	D3DXMatrixInverse(&secondParentWorldMatrixInv, 0, &m_secondParentWorldMatrix);
	D3DXVec3TransformCoord(&m_secondChildPosition, &m_position, &secondParentWorldMatrixInv);

	//�L�����N�^�[�R���g���[���[��������
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(0.3f, 1.0f);
	m_playerController.Init(coll, m_position);
	m_playerController.SetGravity(-20.0f);	//�d�͋���

	m_animation.PlayAnimation(IPlayerState::AnimationStand, 0.3f);
	m_animation.SetAnimationEndTime(IPlayerState::AnimationRun, 0.8f);
	m_animation.SetAnimationEndTime(IPlayerState::AnimationJump, 1.1f);
	m_animation.SetAnimationLoopflg(IPlayerState::AnimationJump, false);
	m_animation.SetAnimationLoopflg(IPlayerState::AnimationPose, false);
	m_animation.SetAnimationLoopflg(IPlayerState::AnimationDead, false);
	
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

	if (sceneManager->GetScene() == SceneManager::stateStageSelect) {
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}

	//����������t���O�����Ă�
	if (m_position.y <= -20.0f) {
		m_fallPlayer = true;
	}

	//�o�l�ɓ��������Ƃ��W�����v
	if (m_treadOnSpring) {
		m_moveSpeed.y = 0.0f;
		m_moveSpeed.y += m_jumpSpeed * 2;
		m_playerController.Jump();
		m_animation.PlayAnimation(IPlayerState::AnimationNo::AnimationJump);
		m_treadOnSpring = false;
	}

	//�G�𓥂񂾂�W�����v
	if (m_treadOnEnemy) {
		m_moveSpeed.y = 0.0f;
		m_moveSpeed.y += m_jumpSpeed;
		m_playerController.Jump();
		m_animation.PlayAnimation(IPlayerState::AnimationNo::AnimationJump);
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
		m_moveSpeed += m_moveFloorSpeed - m_airResistance;
	}
	else if (m_moveFloor2Inertia) {
		m_ineltiaTime += Timer::GetFrameDeltaTime();
		//��C��R�ŏ��������̑��x�����炷
		m_airResistance = m_moveFloor2Speed * 60.0f;
		D3DXVec3Normalize(&m_airResistance, &m_airResistance);
		m_airResistance *= m_ineltiaTime;
		m_moveFloor2Speed *= 60.0f;
		m_moveSpeed += m_moveFloor2Speed - m_airResistance;
	}
	if (GetIsOnGround())
	{
		m_moveFloorInertia = false;
		m_moveFloor2Inertia = false;
		m_ineltiaTime = 0.0f;
	}

	//��ԋ߂��̈ړ����̃��[���h�s����擾
	if (map != nullptr && !map->GetMoveFloorList().empty()) {
		m_moveFloorWorldMatrix = map->GetMoveFloorWorldMatrix(m_position);
	}
	if (map != nullptr && !map->GetMoveFloor2List().empty()) {
		m_moveFloor2WorldMatrix = map->GetMoveFloor2WorldMatrix(m_position);
	}
	//�ړ����ɓ�����������Ă���
	if (m_playerController.IsOnMoveFloor()) {
		if (m_parentFirstHit) {
			//�e���猩���v���C���[�̍��W���X�V
			D3DXMATRIX moveFloorWorldMatrixInv;
			D3DXMatrixInverse(&moveFloorWorldMatrixInv, NULL, &m_moveFloorWorldMatrix);
			D3DXVec3TransformCoord(&m_moveFloorChildPosition, &m_position, &moveFloorWorldMatrixInv);
			m_parentFirstHit = false;
		}
		//�v���C���[�̃��[���h���W�ɕϊ�����
		D3DXVec3TransformCoord(&m_position, &m_moveFloorChildPosition, &m_moveFloorWorldMatrix);
		m_playerController.SetPosition(m_position);

		if (m_playerController.IsJump()) {
			m_moveFloorInertia = true;
		}

		m_playerController.SetMoveSpeed(m_moveSpeed);
		//�L�����N�^�[�R���g���[���[�����s
		m_playerController.Execute();
		//���W��ݒ�
		m_position = m_playerController.GetPosition();
		//�e���猩���v���C���[�̍��W���X�V
		D3DXMATRIX moveFloorWorldMatrixInv;
		D3DXMatrixInverse(&moveFloorWorldMatrixInv, NULL, &m_moveFloorWorldMatrix);
		D3DXVec3TransformCoord(&m_moveFloorChildPosition, &m_position, &moveFloorWorldMatrixInv);
	}
	else if (m_playerController.IsOnMoveFloor2()) {
		if (m_secondParentFirstHit) {
			//�e���猩���v���C���[�̍��W���X�V
			D3DXMATRIX moveFloor2WorldMatrixInv;
			D3DXMatrixInverse(&moveFloor2WorldMatrixInv, NULL, &m_moveFloor2WorldMatrix);
			D3DXVec3TransformCoord(&m_moveFloor2ChildPosition, &m_position, &moveFloor2WorldMatrixInv);
			m_secondParentFirstHit = false;
		}
		//�v���C���[�̃��[���h���W�ɕϊ�����
		D3DXVec3TransformCoord(&m_position, &m_moveFloor2ChildPosition, &m_moveFloor2WorldMatrix);
		m_playerController.SetPosition(m_position);

		if (m_playerController.IsJump()) {
			m_moveFloor2Inertia = true;
		}

		m_playerController.SetMoveSpeed(m_moveSpeed);
		//�L�����N�^�[�R���g���[���[�����s
		m_playerController.Execute();
		//���W��ݒ�
		m_position = m_playerController.GetPosition();
		//�e���猩���v���C���[�̍��W���X�V
		D3DXMATRIX moveFloor2WorldMatrixInv;
		D3DXMatrixInverse(&moveFloor2WorldMatrixInv, NULL, &m_moveFloor2WorldMatrix);
		D3DXVec3TransformCoord(&m_moveFloor2ChildPosition, &m_position, &moveFloor2WorldMatrixInv);
	}
	//�u���b�N�ɓ���������
	else if (m_playerController.IsOnBlock() == true)
	{
		if (m_parentFirstHit) {
			//�e�̃��[���h�s�񂩂�t�s��𐶐�
			D3DXMATRIX parentWorldMatrixInv;
			D3DXMatrixInverse(&parentWorldMatrixInv, NULL, &m_parentWorldMatrix);
			D3DXVec3TransformCoord(&m_childPosition, &m_position, &parentWorldMatrixInv);
			m_parentFirstHit = false;
		}

		//�v���C���[�̃��[���h���W�ɕϊ�����
		D3DXVec3TransformCoord(&m_position, &m_childPosition, &m_parentWorldMatrix);
		m_playerController.SetPosition(m_position);

		//�v���C���[�̈ړ����x��ݒ�
		m_playerController.SetMoveSpeed(m_moveSpeed);
		//�L�����N�^�[�R���g���[���[�����s
		m_playerController.Execute();
		//���W��ݒ�
		m_position = m_playerController.GetPosition();

		//�e���猩���v���C���[�̍��W���X�V
		D3DXMATRIX worldMatrixInv;
		D3DXMatrixInverse(&worldMatrixInv, NULL, &m_parentWorldMatrix);
		D3DXVec3TransformCoord(&m_childPosition, &m_position, &worldMatrixInv);
	}
	//�u���b�N2�ɓ���������
	else if (m_playerController.IsOnBlock2() == true)
	{
		if (m_secondParentFirstHit) {
			//�e�̃��[���h�s�񂩂�t�s��𐶐�
			D3DXMATRIX secondParentWorldMatrixInv;
			D3DXMatrixInverse(&secondParentWorldMatrixInv, NULL, &m_secondParentWorldMatrix);
			D3DXVec3TransformCoord(&m_secondChildPosition, &m_position, &secondParentWorldMatrixInv);
			m_secondParentFirstHit = false;
		}

		//�v���C���[�̃��[���h���W�ɕϊ�����
		D3DXVec3TransformCoord(&m_position, &m_secondChildPosition, &m_secondParentWorldMatrix);
		m_playerController.SetPosition(m_position);
		//�v���C���[�̈ړ����x��ݒ�
		m_playerController.SetMoveSpeed(m_moveSpeed);
		//�L�����N�^�[�R���g���[���[�����s
		m_playerController.Execute();
		//���W��ݒ�
		m_position = m_playerController.GetPosition();

		//�e���猩���v���C���[�̍��W���X�V
		D3DXMATRIX worldMatrixInv;
		D3DXMatrixInverse(&worldMatrixInv, NULL, &m_secondParentWorldMatrix);
		D3DXVec3TransformCoord(&m_secondChildPosition, &m_position, &worldMatrixInv);
	}
	else {
		//�v���C���[�̈ړ����x��ݒ�
		m_playerController.SetMoveSpeed(m_moveSpeed);
		//�L�����N�^�[�R���g���[���[�����s
		m_playerController.Execute();
		//���W��ݒ�
		m_position = m_playerController.GetPosition();
		m_parentFirstHit = true;
		m_secondParentFirstHit = true;
	}

	//�A�j���[�V�������ς���Ă�����ύX
	if (m_currentAnim != m_prevAnim) {
		m_animation.PlayAnimation(m_currentAnim, 0.3f);
	}
	
	//�O�̃A�j���[�V�������X�V
	m_prevAnim = m_currentAnim;

	//�A�j���[�V�����̍X�V
	m_animation.Update(1.0f / 60.0f);

	//���[���h�s����X�V
	m_model.UpdateWorldMatrix(m_position, m_rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}

void Player::Render()
{
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

void Player::RenderShadow(D3DXMATRIX * viewMatrix, D3DXMATRIX * projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (player != nullptr && gameCamera != nullptr){
		m_model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		m_model.Draw(viewMatrix, projMatrix);
		m_model.SetDrawShadowMap(false, false);
	}
}

void Player::SilhouetteRender(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix)
{
	if (player != nullptr && gameCamera != nullptr) {
		m_model.SetSilhouetteRender(true);
		m_model.Draw(viewMatrix, projMatrix);
		m_model.SetSilhouetteRender(false);
	}
}