#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Light.h"

class Star : public GameObject
{
public:
	//�R���X�g���N�^
	Star();

	//�f�X�g���N�^
	~Star();

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

	//�X�^�[�l���t���O���擾
	bool GetStar()
	{
		return flag;
	}
private:
	SkinModel model;			//�X�L�����f��
	SkinModelData modelData;	//�X�L�����f���f�[�^
	Light light;				//���C�g
	D3DXVECTOR3	position;		//���W
	D3DXQUATERNION rotation;	//��]
	D3DXVECTOR3 InitPosition;	//�������W
	bool flag = false;			//�X�^�[�l���t���O
	float moveSpeed = 0.05f;	//�ړ����x
	float timer = 0.0f;
};