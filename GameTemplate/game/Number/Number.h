#pragma once

#include "myEngine/GameObject/GameObject.h"
#include "myEngine/Graphics/Sprite.h"

class Number{
public:
	//�R���X�g���N�^
	Number();

	//�f�X�g���N�^
	~Number();

	//������
	void Init(D3DXVECTOR2 numPos, D3DXVECTOR2 numSize);

	//���l��ݒ�
	void NumSet(int n);

	//�`��
	void Render();
private:
	Sprite* m_number[10];
	int num = 0;
};