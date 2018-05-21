#pragma once

#include "myEngine/GameObject/GameObject.h"

struct CoinInfo {
	D3DXVECTOR3 position;		//���W
	D3DXQUATERNION rotation;	//��]
};

class Coin : public GameObject {
public:
	//�R���X�g���N�^
	Coin();

	//�f�X�g���N�^
	~Coin();

	//������
	//pos	���W
	//rot	��]
	void Init(int numInstancing);

	bool Start();

	//�X�V
	void Update();

	//�`��
	void Render();

	//�V���h�E�}�b�v�`��
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);

	//�C���X�^���V���O�`��p�̃��[���h�s���������
	void InitInstancingWorldMatrix();

	//�C���X�^���V���O�`��p�̃��[���h�s����X�V
	void UpdateInstancingWorldMatrix();

	//�R�C���̍��W�Ɖ�]��ۑ�
	void SetCoinInfoList(std::list<CoinInfo> coinInfoList)
	{
		m_coinInfoList = coinInfoList;
	}

private:
	SkinModel model;			//�X�L�����f��
	SkinModelData modelData;	//�X�L�����f���f�[�^
	Light light;				//���C�g
	//D3DXVECTOR3	position;		//���W
	//D3DXQUATERNION rotation;	//��]
	D3DXVECTOR3 scale;			//�g�嗦
	D3DXVECTOR3 InitPosition;	//�������W
	bool flag = false;			//�R�C���l���t���O
	float moveSpeed = 0.05f;	//�ړ����x
	int m_numInstancing = 0;
	std::list<CoinInfo> m_coinInfoList;
};