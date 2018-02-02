#pragma once
#include "myEngine/Graphics/Sprite.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Camera.h"

class TitleScene : public GameObject{
public:
	//�R���X�g���N�^
	TitleScene();

	//�f�X�g���N�^
	~TitleScene();

	//������
	void Initialize();

	//�X�V
	void Update();

	//�`��
	void Render();

	//����{�^�������������ǂ���
	bool GetisDeside() {
		return isDeside;
	}

private:
	Sprite* sprite;				//�X�v���C�g
	bool isDeside = false;		//����{�^������������
	float alpha = 1.0f;			//�s�����x�B1.0�͍�
	float timer = 0.0f;			//�^�C�}�[
};
