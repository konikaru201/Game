#include "stdafx.h"
#include "StoneMonster.h"
#include "Scene/SceneManager.h"
#include "Player/Player.h"
#include "myEngine/sound/SoundSource.h"

StoneMonster::StoneMonster() :
	m_stoneMonsterStateMachine(this)
{
}

StoneMonster::~StoneMonster()
{
}

void StoneMonster::Init(D3DXVECTOR3 pos, D3DXQUATERNION rot)
{
	//���f���̏�����
	m_modelData.LoadModelData("Assets/modelData/StoneMonster.x", NULL);
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

	m_model.UpdateWorldMatrix(pos, rot, { 1.0f,1.0f,1.0f });

	m_position = pos;
	m_rotation = rot;
	m_scale = { 1.0f,1.0f,1.0f };

	//���̂̍쐬
	CapsuleCollider* coll = new CapsuleCollider;
	coll->Create(0.3f, 0.4f);
	m_characterController.Init(coll, m_position);
}

bool StoneMonster::Start()
{
	//�e��`�悷��t���O�𗧂Ă�
	SetRenderToShadow();

	goMgr->AddGameObject(&m_stoneMonsterStateMachine);

	//��ԋ߂��ړ����̃��[���h�s����擾
	if (!map->GetMoveFloorList().empty()){
		m_parentWorldMatrix = map->GetMoveFloorWorldMatrix(m_position);
		m_moveFloorPosition = map->GetMoveFloorPosition(m_position);
	}
	if (!map->GetMoveFloor2List().empty()) {
		m_secondParentWorldMatrix = map->GetMoveFloor2WorldMatrix(m_position);
		m_moveFloor2Position = map->GetMoveFloor2Position(m_position);
	}

	//�ŏ��ɐe�̃��[���h�s�񂩂玩�g�̃��[�J�����W���v�Z
	//�L�����N�^�[�R���g���[���[�����s
	m_characterController.Execute();
	if (m_characterController.IsOnMoveFloor()) {
		//�e�̃��[���h�s�񂩂�t�s��𐶐�
		D3DXMATRIX parentWorldMatrixInv;
		D3DXMatrixInverse(&parentWorldMatrixInv, NULL, &m_parentWorldMatrix);
		D3DXVec3TransformCoord(&m_childPosition, &m_position, &parentWorldMatrixInv);
		m_moveFloorHit = true;
	}
	if (m_characterController.IsOnMoveFloor2()) {
		//�e�̃��[���h�s�񂩂�t�s��𐶐�
		D3DXMATRIX secondParentWorldMatrixInv;
		D3DXMatrixInverse(&secondParentWorldMatrixInv, NULL, &m_secondParentWorldMatrix);
		D3DXVec3TransformCoord(&m_secondChildPosition, &m_position, &secondParentWorldMatrixInv);
		m_moveFloor2Hit = true;
	}

	return true;
}

void StoneMonster::Update()
{
	//�V�[���؂�ւ���
	if (sceneManager->GetChangeSceneFlag() || m_deadTimer >= 0.5f)
	{
		//��ԃN���X�̎��S�t���O�𗧂Ă�
		m_stoneMonsterStateMachine.SetIsChangeState(true);
		m_stoneMonsterStateMachine.Release();
		//���S�t���O�𗧂Ă�
		SetisDead();
		//���̂��폜
		m_characterController.RemoveRigidBoby();
		return;
	}	

	//���܂ꂽ�玀�S�^�C�}�[���J�E���g
	if (m_isStepOn) {
		m_deadTimer += Timer::GetFrameDeltaTime();
	}

	if(!player->GetHitEnemy()){
		//�v���C���[�Ƃ̓����蔻��
		D3DXVECTOR3 playerPos = player->GetPosition();
		D3DXVECTOR3 toPlayerPos = playerPos - m_position;
		float length = D3DXVec3Length(&toPlayerPos);
		if (length <= 1.0f) {
			D3DXVECTOR3 playerMoveSpeed = player->GetMoveSpeed();
			D3DXVECTOR3 toPlayerPosY = { 0.0f,toPlayerPos.y,0.0f };
			D3DXVECTOR3 toPlayerPosXZ = { toPlayerPos.x,0.0f,toPlayerPos.z };
			float lengthY = D3DXVec3Length(&toPlayerPosY);
			float lengthXZ = D3DXVec3Length(&toPlayerPosXZ);
			if (toPlayerPos.y > 0.0f && lengthY <= 0.5f && lengthXZ <= 0.6f) {
				player->SetTreadOnEnemy(true);
				m_isStepOn = true;
				m_scale.y = 0.1f;

				CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
				SE->Init("Assets/sound/Humituke.wav");
				SE->Play(false);
			}
			else if (lengthY <= 0.4f && lengthXZ <= 0.7f) {
				player->SetHitEnemy(true);
				m_isHitPlaer = true;
			}
		}
	}

	//���t���[���e�̃��[���h�s����X�V
	if (m_moveFloorHit == true && !map->GetMoveFloorList().empty()){
		m_parentWorldMatrix = map->GetMoveFloorWorldMatrix(m_position);
		m_moveFloorPosition = map->GetMoveFloorPosition(m_position);
	}
	else if (m_moveFloor2Hit == true && !map->GetMoveFloor2List().empty()) {
		m_secondParentWorldMatrix = map->GetMoveFloor2WorldMatrix(m_position);
		m_moveFloor2Position = map->GetMoveFloor2Position(m_position);
	}

	//�ړ����ɓ������Ă���
	if (m_moveFloorHit) {
		//���[���h���W�ɕϊ�����
		D3DXVec3TransformCoord(&m_position, &m_childPosition, &m_parentWorldMatrix);
		m_characterController.SetPosition(m_position);

		m_characterController.SetMoveSpeed(m_moveSpeed);
		//�L�����N�^�[�R���g���[���[�����sD3D
		m_characterController.Execute();
		//���W��ݒ�
		m_position = m_characterController.GetPosition();

		//�e���猩���v���C���[�̍��W���X�V
		D3DXMATRIX worldMatrixInv;
		D3DXMatrixInverse(&worldMatrixInv, NULL, &m_parentWorldMatrix);
		D3DXVec3TransformCoord(&m_childPosition, &m_position, &worldMatrixInv);
	}
	else if (m_moveFloor2Hit){
		//���[���h���W�ɕϊ�����
		D3DXVec3TransformCoord(&m_position, &m_secondChildPosition, &m_secondParentWorldMatrix);
		m_characterController.SetPosition(m_position);

		m_characterController.SetMoveSpeed(m_moveSpeed);
		//�L�����N�^�[�R���g���[���[�����s
		m_characterController.Execute();
		//���W��ݒ�
		m_position = m_characterController.GetPosition();

		//�e���猩�����W���X�V
		D3DXMATRIX worldMatrixInv;
		D3DXMatrixInverse(&worldMatrixInv, NULL, &m_secondParentWorldMatrix);
		D3DXVec3TransformCoord(&m_secondChildPosition, &m_position, &worldMatrixInv);
	}
	else {
		m_characterController.SetMoveSpeed(m_moveSpeed);
		//�L�����N�^�[�R���g���[���[�����s
		m_characterController.Execute();
		//���W��ݒ�
		m_position = m_characterController.GetPosition();
	}

	m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
}

void StoneMonster::Render()
{
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

void StoneMonster::RenderShadow(D3DXMATRIX * viewMatrix, D3DXMATRIX * projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (gameCamera != nullptr) {
		m_model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		m_model.Draw(viewMatrix, projMatrix);
		m_model.SetDrawShadowMap(false, false);
	}
}
