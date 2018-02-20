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

	//�V���h�E�}�b�v�`��
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);

	//���W���擾
	const D3DXVECTOR3& GetPosition()
	{
		return position;
	}
private:
	SkinModel model;			//�X�L�����f��
	SkinModelData modelData;	//�X�L�����f���f�[�^
	Light light;
	D3DXVECTOR3	position;		//���W
	D3DXQUATERNION rotation;	//��]
	D3DXVECTOR3 InitPosition;	//�������W
	bool flag = false;			//�R�C���l���t���O
	float moveSpeed = 0.05f;	//�ړ����x
};