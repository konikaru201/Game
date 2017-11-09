#pragma once
#include "myEngine/Graphics/Sprite.h"
#include "myEngine/GameObject/GameObject.h"

class ResultScene : public GameObject {
public:
	//�R���X�g���N�^
	ResultScene();

	//�f�X�g���N�^
	~ResultScene();

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
	float alpha = 1.0f;
	float timer = 0.0f;
};