#pragma once

#include "myEngine/GameObject/GameObject.h"

class Silhouette : public GameObject
{
public:
	//�R���X�g���N�^
	Silhouette();

	//�f�X�g���N�^�f�X�g���N�^
	~Silhouette();

	//�X�V����O�ɌĂ΂��֐�
	bool Start();

	//�X�V
	void Update();

	//�`��
	void Render();
};