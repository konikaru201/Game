#pragma once

#include "myEngine/GameObject/GameObject.h"

class DepthStencilRender : public GameObject
{
public:
	//�R���X�g���N�^
	DepthStencilRender();

	//�f�X�g���N�^�f�X�g���N�^
	~DepthStencilRender();

	//�X�V����O�ɌĂ΂��֐�
	bool Start();

	//�X�V
	void Update();

	//�`��
	void Render();
};