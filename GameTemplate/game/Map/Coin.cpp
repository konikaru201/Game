#include "stdafx.h"
#include "Coin.h"
#include "Scene/SceneManager.h"
#include "myEngine/Sound/SoundSource.h"

Coin::Coin()
{
}

Coin::~Coin()
{
}

void Coin::Init(int numInstancing)
{
	//���f���̏�����
	m_model.SetInstancingDraw(true);
	m_numInstancing = numInstancing;
	//�C���X�^���V���O�`�悷�鐔��ݒ�
	m_model.SetNumInstancing(m_numInstancing);
	m_modelData.LoadModelData("Assets/modelData/Coin.x", NULL);
	m_model.Init(&m_modelData);

	m_light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	m_light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	m_light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	m_light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	m_light.SetAmbientLight(D3DXVECTOR4(2.0f, 2.0f, 2.0f, 1.0f));
	m_model.SetLight(&m_light);
	m_model.UpdateWorldMatrix({ 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f,1.0f }, { 1.0f,1.0f,1.0f });

	m_scale = { 0.06f,0.06f,0.06f };
	
	//�e��`�悷��t���O�𗧂Ă�
	SetRenderToShadow();

	//�C���X�^���V���O�`��p�̃��[���h�s���������
	InitInstancingWorldMatrix();
}

bool Coin::Start()
{

	return true;
}

void Coin::Update()
{
	//�V�[���؂�ւ����ɍ폜
	if (sceneManager->GetChangeSceneFlag()) {
		SetisDead();
		m_coinInfoList.clear();
		return;
	}

	UpdateInstancingWorldMatrix();
}

void Coin::Render()
{
	m_model.Draw(&gameCamera->GetViewMatrix(), &gameCamera->GetProjectionMatrix());
}

void Coin::RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	if (gameCamera != nullptr) {
		m_model.SetDrawShadowMap(isDrawShadowMap, isRecieveShadow);
		m_model.Draw(viewMatrix, projMatrix);
		m_model.SetDrawShadowMap(false, false);
	}
}

void Coin::InitInstancingWorldMatrix()
{
	int index = 0;
	for (auto& coinInfo : m_coinInfoList) {
		D3DXVECTOR3 pos = coinInfo.position;
		D3DXQUATERNION rot = coinInfo.rotation;
		//���[���h�s��̌v�Z
		D3DXMATRIX mTrans, mScale, mRotationMatrix;
		D3DXMatrixScaling(&mScale, m_scale.x, m_scale.y, m_scale.z);
		D3DXMatrixTranslation(&mTrans, pos.x, pos.y, pos.z);
		D3DXMatrixRotationQuaternion(&mRotationMatrix, &rot);

		IWorldMatrix[index] = mScale * mRotationMatrix * mTrans;
		index++;
	}
}

void Coin::UpdateInstancingWorldMatrix()
{
	std::list<CoinInfo>::iterator it;

	int index = 0;
	for (it = m_coinInfoList.begin(); it != m_coinInfoList.end(); ++it) {
		D3DXVECTOR3 position = (it)->position;
		D3DXQUATERNION rotation = (it)->rotation;
		//��]���v�Z
		float angle = 1.0f * cPI / 180.0f;
		D3DXQUATERNION rot = { 0.0f,1.0f,0.0f,1.0f };
		D3DXVECTOR3 up = { 0.0f,1.0f,0.0f };
		D3DXQuaternionRotationAxis(&rot, &up, angle);
		D3DXQuaternionMultiply(&rotation, &rotation, &rot);
		//��]���X�V
		(it)->rotation = rotation;

		//�v���C���[�Ƃ̋��������߂�
		D3DXVECTOR3 PlayerPos = player->GetPosition();
		D3DXVECTOR3 toPlayer = position - PlayerPos;
		float length = D3DXVec3Length(&toPlayer);
		if (length <= 0.9f) {
			//�R�C���̖������J�E���g
			sceneManager->GetCoinUI()->CoinCount();
			it = m_coinInfoList.erase(it);
			m_numInstancing--;
			//����炷
			CSoundSource* SE = goMgr->NewGameObject<CSoundSource>();
			SE->Init("Assets/sound/coin.wav");
			SE->Play(false);

			return;
		}

		//���[���h�s��̌v�Z
		D3DXMATRIX mTrans, mScale, mRotationMatrix;
		D3DXMatrixScaling(&mScale, m_scale.x, m_scale.y, m_scale.z);
		D3DXMatrixTranslation(&mTrans, position.x, position.y, position.z);
		D3DXMatrixRotationQuaternion(&mRotationMatrix, &rotation);

		IWorldMatrix[index] = mScale * mRotationMatrix * mTrans;
		index++;
	}

	m_model.SetNumInstancing(m_numInstancing);
}
