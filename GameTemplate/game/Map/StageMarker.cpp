#include "stdafx.h"
#include "StageMarker.h"
#include "Scene/SceneManager.h"

StageMarker::StageMarker()
{
}

StageMarker::~StageMarker()
{
}

void StageMarker::Init(D3DXVECTOR3 position, D3DXQUATERNION rotation)
{
	m_modelData.LoadModelData("Assets/modelData/stageMarker.x", NULL);
	m_model.Init(&m_modelData);
	//���C�g��������
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
	m_model.UpdateWorldMatrix({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 1.0 }, { 1.0f,1.0f,1.0f });

	m_position = position;
	m_rotation = rotation;

	//�Փ˔���̏�����
	//�X�L�����f�����烁�b�V���R���C�_�[���쐬����
	D3DXMATRIX* rootBoneMatrix = m_modelData.GetRootBoneWorldMatrix();
	m_meshCollider.CreateFromSkinModel(&m_model, rootBoneMatrix);

	//���̂���邽�߂̏���ݒ�
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_meshCollider;		//���̂̃R���W������ݒ肷��
	rbInfo.mass = 0.0f;					//���ʂ�0�ɂ���Ɠ����Ȃ����̂ɂȂ�
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	//���̂��쐬
	m_rigidBody.Create(rbInfo);

	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
	trans.setRotation(btQuaternion(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w));

	//�쐬�������̂𕨗����[���h�ɒǉ�
	g_physicsWorld->AddRigidBody(&m_rigidBody);
}

bool StageMarker::Start()
{
	//�e��`�悷��t���O�𗧂Ă�
	SetRenderToShadow();

	//�e�̃��[���h�s����擾
	m_parentWorldMatrix = map->GetEarthInstance()->GetWorldMatrix();
	//�e�̃��[���h�s�񂩂�t�s����쐬
	D3DXMATRIX parentWorldMatrixInv;
	D3DXMatrixInverse(&parentWorldMatrixInv, NULL, &m_parentWorldMatrix);
	D3DXVec3TransformCoord(&m_childPosition, &m_position, &parentWorldMatrixInv);
	//�e�̃��[���h�s�񂩂�N�H�[�^�j�I�����쐬
	D3DXQUATERNION parentRotationMatrixInv;
	D3DXQuaternionRotationMatrix(&parentRotationMatrixInv, &parentWorldMatrixInv);
	//�e���猩���N�H�[�^�j�I���ɕϊ�
	D3DXQuaternionMultiply(&m_childRotation, &m_rotation, &parentRotationMatrixInv);

	return true;
}

void StageMarker::Update()
{
	if (sceneManager->GetChangeSceneFlag())
	{
		SetisDead();
		//���̂��폜
		g_physicsWorld->RemoveRigidBody(&m_rigidBody);
		return;
	}

	if (map->GetEarthInstance()->GetIsRotate()) {
		//�e�̃��[���h�s����擾
		m_parentWorldMatrix = map->GetEarthInstance()->GetWorldMatrix();
		//���[���h���W�ɕϊ�����
		D3DXVec3TransformCoord(&m_position, &m_childPosition, &m_parentWorldMatrix);
		//�e�̃��[���h�s�񂩂�t�s����쐬
		D3DXMATRIX parentWorldMatrixInv;
		D3DXMatrixInverse(&parentWorldMatrixInv, NULL, &m_parentWorldMatrix);
		D3DXVec3TransformCoord(&m_childPosition, &m_position, &parentWorldMatrixInv);
		//�e�̃��[���h�s�񂩂�N�H�[�^�j�I�����쐬
		D3DXQUATERNION parentRotation;
		D3DXQuaternionRotationMatrix(&parentRotation, &m_parentWorldMatrix);
		//�e�̃N�H�[�^�j�I�����g���ĉ�]������
		D3DXQuaternionMultiply(&m_rotation, &m_childRotation, &parentRotation);
		//�e�̃��[���h�s��̋t�s�񂩂�N�H�[�^�j�I�����쐬
		D3DXQUATERNION parentRotationMatrixInv;
		D3DXQuaternionRotationMatrix(&parentRotationMatrixInv, &parentWorldMatrixInv);
		//�e���猩���N�H�[�^�j�I���ɕϊ�
		D3DXQuaternionMultiply(&m_childRotation, &m_rotation, &parentRotationMatrixInv);
	}

	D3DXVECTOR3 toPlayerPos = player->GetPosition() - m_position;
	float length = D3DXVec3Length(&toPlayerPos);
	if (length <= 0.8f) {
		sceneManager->GetstageSelectScene()->SetBottonReneder(true, 0);
		if (pad->IsTrigger(pad->enButtonA)) {
			m_stageChange = true;
			player->SetChangeStage(m_stageChange);
		}
	}
	else {
		sceneManager->GetstageSelectScene()->SetBottonReneder(false, 0);
	}

	if (m_stageChange) {
		if (player->GetAnimationEnd()) {
			sceneManager->GetstageSelectScene()->SetChangeStage(true, 1);
		}
	}

	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
	trans.setRotation(btQuaternion(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w));

	m_model.UpdateWorldMatrix(m_position, m_rotation, { 1.0f,1.0f,1.0f });
}

void StageMarker::Render()
{
	m_model.SetDrawShadowMap(false, false);
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

void StageMarker::RenderShadow(D3DXMATRIX * viewMatrix, D3DXMATRIX * projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (gameCamera != nullptr) {
		m_model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		m_model.Draw(viewMatrix, projMatrix);
		m_model.SetDrawShadowMap(false, false);
	}
}
