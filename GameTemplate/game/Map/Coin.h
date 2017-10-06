#pragma once

#include "myEngine/GameObject/GameObject.h"

class Coin : public GameObject {
public:
	//�R���X�g���N�^
	Coin();

	//�f�X�g���N�^
	~Coin();

	//������
	//pos	���W
	//rot	��]
	void Init(D3DXVECTOR3 pos, D3DXQUATERNION rot);

	//�X�V
	void Update();

	//�`��
	void Render();
private:
	SkinModel model;			//�X�L�����f��
	SkinModelData modelData;	//�X�L�����f���f�[�^

	D3DXVECTOR3	position;		//���W
	D3DXQUATERNION rotation;	//��]
	D3DXVECTOR3 InitPosition;	//�������W
	bool flag = false;			//�R�C���l���t���O
	float moveSpeed = 0.05f;	//�ړ����x
};